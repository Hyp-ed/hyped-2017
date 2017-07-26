/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Jack_Gargan
 */

import java.net.*;

public class UDPReceiverTest
{
    public static void main (String args[]) throws Exception
    {
         byte[] receiveData = new byte[1024];
          DatagramSocket socket = new DatagramSocket();
         DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
         socket.receive(receivePacket);
         String data = new String(receivePacket.getData());
         
         // Not finished
    }
}
