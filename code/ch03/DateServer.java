import java.net.*;
import java.io.*;

public class DateServer {
    public static void main(String[] args) {
        try {
            // create a socket to listen to port 3000
            ServerSocket sock=new ServerSocket(3000);
            // listening for connections
            while(true) {
                // accept a connection
                Socket client=sock.accept();
                // write system date to the socket
                PrintWriter pout=new PrintWriter(client.getOutputStream(),true);
                pout.println(new java.util.Date().toString());
                // close the socket
                client.close();
            }
        }
        catch(IOException ioe) {
            System.err.println(ioe);
        }
    }
}