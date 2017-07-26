
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
import java.nio.ByteBuffer;

public class Server
{
    private static PiList _list = new PiList();
    
   final private static int _podPort = 5695;
   private static int _spaceXPort = 3000;
   private static String _spaceXIP = "192.168.0.1";
   private static ServerSocket _server;
   private static Socket _podSocket;
   // Implement SpaceX UDP socket via Datagram
   //private static Server pointer = this;
   private static GUI frontEnd = new GUI(/*pointer*/);
   
   public static void main(String args[]) throws IOException
   {
       try
       {
           //frontEnd.setParent(this);
           frontEnd.setVisible(true);
           
           _server = new ServerSocket(_podPort);
           frontEnd.printToConsole("AWAITING SIGNAL FROM POD COMPUTERS...");
           
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
                
               sendToPod(_podSocket); 
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
            //piName = piName.substring(0, piName.indexOf("|"));
            // CANNOT CLOSE INPUT OBJ. OR POINT TO NULL AS THIS WOULD CLOSE THE SOCKET DATA STREAM.
            return piName;
        } catch(IOException e) 
        { 
            frontEnd.printToConsole("ERROR IN 'getPiName()': " + e.getMessage());
            return "0"; 
        }
    }
    
    public static void sendToPod(Socket piConnection) throws Exception
    {
        Socket temp = piConnection;
        PrintWriter tempOut = new PrintWriter(temp.getOutputStream());
            
        tempOut.println(1); //message received
        tempOut.flush(); 
            
    }
    
    public static void sendToSpaceX
    (
         byte status, byte team_id, int acceleration, int position, 
         int velocity/*, int voltage, int temperature, int current, 
         int podTemp*/
    ) throws IOException
            
    {
        // Test by writing UDP client receiver.
        
        DatagramSocket spaceXSocket = new DatagramSocket(_spaceXPort);
        ByteBuffer buf = ByteBuffer.allocate(34); // BigEndian by default
        buf.put(team_id);
        buf.put(status);
        buf.putInt(acceleration);
        buf.putInt(position);
        buf.putInt(velocity);
        buf.putInt(0);
        buf.putInt(0);
        buf.putInt(0);
        buf.putInt(0);
        buf.putInt(0);
        InetAddress IP =  InetAddress.getByName(_spaceXIP);
        DatagramPacket packet = new DatagramPacket(buf.array(), buf.limit(), IP, _spaceXPort);
        spaceXSocket.send(packet);
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
        
        public boolean getStatus() { return subSock.isConnected(); }
        
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
                    
                    byte status = 1, team_id = 0;
                    int acceleration = 0, position = 0, velocity = 0, battery_voltage = 0, 
                            battery_current = 0, battery_temperature = 0,
                                pod_temperature = 0;
                    
                    while(true)
                    {
                        this.verifConnection();
                        
                        if (!_input.hasNext()) return;
                        
                        message = _input.nextLine();
                        //message = message.substring(0, message.indexOf("|"));
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
                        
                        /*if(message.contains("CMD"))
                        {
                            if (message.contains("CMD1"))
                            {
                                frontEnd.printPodTemperature(Integer.parseInt(message.substring(4)));
                                _out.print(1);
                                receipt(subSock);
                            }
                        }*/ // change to switch statement, i.e. switch (message.substring(0, 4)) case "CMD1"...
                        
                     
                        switch(message.substring(0, 5))
                        {
                            // Encapsulate each parseint within try block, upon error print receipt 0, pi responds...
                            case "CMD01":
                                frontEnd.printAcceleration(Double.parseDouble(message.substring(5)));
                                //_out.print(1);
                                sendToPod(subSock);
                                acceleration = (int) Math.round(Double.parseDouble(message.substring(5)));
                                break;
                            case "CMD02":
                                frontEnd.printVelocity(Double.parseDouble(message.substring(5)));
                                sendToPod(subSock);
                                velocity = (int) Math.round(Double.parseDouble(message.substring(5)));
                                break;
                            case "CMD03":
                                frontEnd.printPosition(Double.parseDouble(message.substring(5)));
                                sendToPod(subSock);
                                position = (int) Math.round(Double.parseDouble(message.substring(5)));
                                break;
                            case "CMD04":
                                frontEnd.printPodTemperature(Double.parseDouble(message.substring(5)));
                                sendToPod(subSock);
                                pod_temperature = (int) Math.round(Double.parseDouble(message.substring(5)));
                                break;
                            case "CMD05":
                                frontEnd.printStripeCount(Double.parseDouble(message.substring(5)));
                                sendToPod(subSock);
                                break;
                            case "CMD06":
                                frontEnd.printGroundProximity(Double.parseDouble(message.substring(5)));
                                sendToPod(subSock);
                                break;
                            case "CMD07":
                                frontEnd.printRailProximity(Double.parseDouble(message.substring(5)));
                                sendToPod(subSock);
                                break;
                            case "CMD08":
                                frontEnd.printPusherDetection(Integer.parseInt(message.substring(5)));
                                sendToPod(subSock);
                                break;
                            case "CMD09":
                                frontEnd.printBattery1Temperature(Double.parseDouble(message.substring(5)));
                                sendToPod(subSock);
                                break;
                            case "CMD10":
                                frontEnd.printBattery1Current(Double.parseDouble(message.substring(5)));
                                sendToPod(subSock);
                                break;
                            case "CMD11":
                                frontEnd.printBattery1Voltage(Double.parseDouble(message.substring(5)));
                                sendToPod(subSock);
                                break;
                            case "CMD12":
                                frontEnd.printBattery2Temperature(Double.parseDouble(message.substring(5)));
                                sendToPod(subSock);
                                break;
                            case "CMD13":
                                frontEnd.printBattery2Current(Double.parseDouble(message.substring(5)));
                                sendToPod(subSock);
                                break;
                            case "CMD14":
                                frontEnd.printBattery2Voltage(Double.parseDouble(message.substring(5)));
                                sendToPod(subSock);
                                break;
                            case "CMD15":
                                frontEnd.printBattery3Temperature(Double.parseDouble(message.substring(5)));
                                sendToPod(subSock);
                                break;
                            case "CMD16":
                                frontEnd.printBattery3Voltage(Double.parseDouble(message.substring(5)));
                                sendToPod(subSock);
                                break;
                            case "CMD17":
                                frontEnd.printHydraulicState(Integer.parseInt(message.substring(5)));
                                sendToPod(subSock);
                                break;
                            case "CMD18":
                                frontEnd.printAccum1(Integer.parseInt(message.substring(5)));
                                sendToPod(subSock);
                                break;
                            case "CMD19":
                                frontEnd.printAccum2(Integer.parseInt(message.substring(5)));
                                sendToPod(subSock);
                                break;
                            case "CMD20":
                                frontEnd.printAccum3(Integer.parseInt(message.substring(5)));
                                sendToPod(subSock);
                                break;
                            case "CMD21":
                                frontEnd.printAccum4(Integer.parseInt(message.substring(5)));
                                sendToPod(subSock);
                                break;
                            case "CMD22":
                                frontEnd.setPodStatus(Integer.parseInt(message.substring(5)));
                                sendToPod(subSock);
                                status = (byte)Integer.parseInt(message.substring(5));
                        }
                        
                        //sendToSpaceX(status, team_id, acceleration, position, velocity);
                        // Commented out because IP for SpaceX is currently in use
                    }
                } finally { subSock.close(); _input.close(); _out.close();  }
            } catch (Exception e) { System.err.println("3 "+e); }
        }
    }
   
}
