import java.util.*;
import java.net.*;

public class PiList
{
    private ArrayList<String> ID = new ArrayList<String>();
    private ArrayList<Socket> connections = new ArrayList<Socket>();
    
    public void addPi(String name, Socket sock)
    {
        ID.add(name); connections.add(sock);
    }
    
    public String getPiName(int index) { return ID.get(index); }
    
    public String getPiName(Socket sock)
    {
        return ID.get(connections.indexOf(sock));
    }
    
    public Socket getPiConnection(int index) { return connections.get(index); }

    public Socket getPiConnection(String name) { return connections.get(ID.indexOf(name)); }
    
    public void removePi(String name)
    {
        int index = ID.indexOf(name);
        ID.remove(index);
        connections.remove(index);
    }
    
    public void removePi(int index)
    {
        ID.remove(index);
        connections.remove(index);
    }
    
    public void removePi(Socket sock)
    {
        int index = connections.indexOf(sock);
        ID.remove(index);
        connections.remove(index);
    }
    
    public ArrayList<String> getAllIDs() { return ID; }
    
    public int getNoOfPis() { return ID.size() /*- 1*/; }
    
    public void delete() { ID.clear(); ID = null; connections.clear(); connections = null; }
}
