package com.tang.tcpserver;

import java.net.*;
import java.io.*;

public class TCPserver {  
	public static void main(String[] args) {  
		if(args.length==1){
			int port=Integer.parseInt(args[0]);
			try{
				Thread t=new ServerThread(port);
				t.start();
			}catch(Exception e){
				e.printStackTrace();
			}
		}else{
			Usage();
		}
	}  

	private static void Usage(){
		System.out.println("TCPserver <port>");
	}
}
