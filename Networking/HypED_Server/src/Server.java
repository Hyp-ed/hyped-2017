
/*
 *       Title: HypED Server Code
 *       Autor: Jack Gargan
 * Description: Onboard Pi computers broadcast their sensor data to the IP 
                address of the machine running this program. This program will
                display the data and send it to the SpaceX system over a UDP 
                socket in the expected format.
 */

import java.util.*;
import java.io.*;
import java.net.*;

public class Server
{
    private static PiList _list = new PiList();
    
    final private static int _podPort = 5695, _spaceXPort = 3000;
   private static ServerSocket _server;
   private static Socket _podSocket;
   // Implement SpaceX UDP socket via Datagram
   private static GUI frontEnd = new GUI();
   
   public static void main(String args[]) throws IOException
   {
       try
       {
           frontEnd.setVisible(true);
           // Demonstratory data ----------------------------------------------
           frontEnd.printToConsole("DEMONSTRATION DATA:---");
           //frontEnd.printToConsole("AWAITING PI CONNECTIONS...");
           frontEnd.printBatteryTemperature(5000);
           frontEnd.printVoltage(50);
           frontEnd.printCurrent(20);
           //frontEnd.setMasterOnline(true);
           //frontEnd.setSlave3Online(false);
           frontEnd.setPodStatus(1);
           frontEnd.printToConsole("------------");
           //------------------------------------------------------------------
           
           _server = new ServerSocket(_podPort);
           frontEnd.printToConsole("AWAITING PI CONNECTIONS...");
           
           while(true)
           {
               _podSocket = _server.accept();
                String piName = getPiName(_podSocket);
                _list.addPi(piName, _podSocket);
                frontEnd.printToConsole(piName + " CONNECTION ESTABLISHED"
                         + " from " + _podSocket.getLocalAddress().getHostName());
                
                switch(piName)
                {
                    case "Slave_0":
                        frontEnd.setSlave0Online(true);
                        break;
                    case "Slave_1":
                        frontEnd.setSlave1Online(true);
                        break;
                    case "Slave_2":
                        frontEnd.setSlave2Online(true);
                        break;
                    case "Slave_3":
                        frontEnd.setSlave3Online(true);
                        break;
                    case "Master":
                        frontEnd.setMasterOnline(true);
                }
                
               //receipt(_podSocket); 
               UserThread usr = new UserThread(_podSocket);
               usr.start(); 
           }
            
       }catch(Exception e){}
   }
   
    private static String getPiName(Socket sock)
    {
        try
        {
            Scanner input = new Scanner(sock.getInputStream());
            String piName = input.nextLine();
            piName = piName.substring(0, piName.indexOf("|"));
            // CANNOT CLOSE INPUT OBJ. OR POINT TO NULL AS THIS WOULD CLOSE THE SOCKET DATA STREAM.
            return piName;
        } catch(IOException e) 
        { 
            frontEnd.printToConsole("ERROR IN 'getPiName()': " + e.getMessage());
            return "0"; 
        }
    }
    
    public static void receipt(Socket piConnection) throws Exception
        {
            Socket temp = piConnection;
            PrintWriter tempOut = new PrintWriter(temp.getOutputStream());
            
            tempOut.println("1"); //message received
            tempOut.flush(); 
            
        }
    
    private static class UserThread extends Thread
    {
        
        Socket subSock = null;
        private Scanner _input = null;
        private PrintWriter _out = null;
        String message = "";
        
        public UserThread(Socket sock) { this.subSock = sock; }
        
        private void verifConnection() throws IOException
        {   
            if (subSock.isClosed())
            {
                for (int i = 1; i <= _list.getNoOfPis() + 1; i++)
                    if (_list.getPiConnection(i-1) == subSock)
                    {
                        _list.removePi(i-1);
                        String name = _list.getPiName(i-1);
                        frontEnd.printToConsole(name + " CONNECTION LOST");
                        
                        switch(name)
                        {
                            case "Slave_0":
                                frontEnd.setSlave0Online(false);
                                break;
                            case "Slave_1":
                                frontEnd.setSlave1Online(false);
                                break;
                            case "Slave_2":
                                frontEnd.setSlave2Online(false);
                                break;
                            case "Slave_3":
                                frontEnd.setSlave3Online(false);
                                break;
                            case "Master":
                                frontEnd.setMasterOnline(false);
                        }
                    }
            }
        }
        
        
        
        public void run()
        {
            try
            {
                try
                {
                    _input = new Scanner(subSock.getInputStream());
                    _out = new PrintWriter(subSock.getOutputStream());
                    
                    Socket temp = null;
                    PrintWriter tempOut = null;
                    
                    while(true)
                    {
                        this.verifConnection();
                        
                        if (!_input.hasNext()) return;
                        
                        message = _input.nextLine();
                        message = message.substring(0, message.indexOf("|"));
                        frontEnd.printToConsole(_list.getPiName(subSock) + " sent data: " + message);
                  
                       /* for (int i = 1; i <= _userList.getNoOfUsers() + 1; i++)
                        {
                            temp = _userList.getUserConnection(i-1);
                            tempOut = new PrintWriter(temp.getOutputStream());
                            if (!message.contains("CMD"))
                                tempOut.println(_userList.getUserName(subSock).toUpperCase() + ": " + message);
                            else
                            {
                                tempOut.println(message);
                                if (message.contains("CMD2"))
                                {
                                    _userList.removeUser(subSock);
                                    refreshUserLists();
                                }
                            }
                            tempOut.flush();
                            System.out.println("Sent to: " + temp.getLocalAddress().getHostName());
                        }*/
                        
                        if(message.contains("CMD"))
                        {
                            if (message.contains("CMD1"))
                                frontEnd.printPodTemperature(Integer.parseInt(message.substring(4)));
                        } // change to switch statement, i.e. switch (message.substring(0, 4)) case "CMD1"...
                    }
                } finally { subSock.close(); _input.close(); _out.close();  }
            } catch (Exception e) { System.err.println("3 "+e); }
        }
    }
   
}
