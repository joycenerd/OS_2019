import java.net.*;
import java.io.*;

public class DateClient {
    public static void main(String[] args) {
        try {
            // create a socket and request a connection with port 3000
            Socket sock=new Socket("127.0.0.1",3000);
            // get the message from the server
            InputStream in=sock.getInputStream();
            BufferedReader bin=new BufferedReader(new InputStreamReader(in));
            String line;
            line=bin.readLine();
            // print the message from the server
            while(line!=null) {
                System.out.println(line);
                line=bin.readLine();
            }
            // close the socket
            sock.close();
        }
        catch(IOException ioe) {
            System.err.println(ioe);
        }
    }
}