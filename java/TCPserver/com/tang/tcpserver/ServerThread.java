package com.tang.tcpserver;

import java.util.Random;
import java.io.*;
import java.net.*;

public class ServerThread extends Thread{
	private ServerSocket serverSocket;
	private final static String INITFINISHED="initfinished";
	private final static String INITIALIZE="initialize";
	private final static String USERFILE="userinfo.xml"; 
	private final static String RESET="reset";
	private final static String SUCCESS="success";
	private final static String FAIL="fail";
	private final static String ILLEGAL="illegal";
	private XMLManager xmlmanager;
	private RC4 rc4;

	public ServerThread(int port) throws IOException{
		xmlmanager=new XMLManager(USERFILE);
		serverSocket=new ServerSocket(port);
		//serverSocket.setSoTimeout(10000);
		System.out.println("Listenning on: "+serverSocket.getLocalPort());
	}

	@Override
	public void run(){
		while(true){
			try{
				Socket clientsocket=serverSocket.accept();
				System.out.println("Connected with: "+clientsocket.getRemoteSocketAddress());
				DataInputStream in=new DataInputStream(clientsocket.getInputStream());
				DataOutputStream out=new DataOutputStream(clientsocket.getOutputStream());
				String username=in.readUTF();
				if(username==null||username.equals("")){
					//nothing recieved
				}else{
					if(username.equals("bye")){
						//end
					}else{
						//recieved an username
						User user;
						//todo: read user informatino
						user=xmlmanager.readUser();
						if(user==null||user.invalidate()){
							//todo: use diffie-hellman policy to make the key
							String name,addinfo,password,count;
							in.readUTF();
							out.writeUTF(INITIALIZE);
							//simple random number
							Random random=new Random();
							int tmpKey=random.nextInt(99999);
							out.writeUTF(Integer.toString(tmpKey));
							rc4=new RC4(Integer.toString(tmpKey));
							//save user infomation
							name=rc4.RC4parse(in.readUTF());
							addinfo=rc4.RC4parse(in.readUTF());
							password=rc4.RC4parse(in.readUTF());
							System.out.println(name);
							System.out.println(addinfo);
							System.out.println(password);
							xmlmanager.saveUser(new User(name,addinfo,password,0));
							System.out.println(name+" "+addinfo+" "+password);
							out.writeUTF(rc4.RC4parse(INITFINISHED));
						}else{
							//todo: user exists
							rc4=new RC4(user.getCount()+user.getAddinfo()+user.getPassword());
							System.out.println(user.getCount()+user.getAddinfo()+user.getPassword());
							String name_encrypted=in.readUTF();
							if(user.getName().equals(username)){
								//todo: password challenge
								if(username.equals(rc4.RC4parse(name_encrypted))){
									//todo: successed
									//unlock
									out.writeUTF(SUCCESS);
									user.incCount();
									xmlmanager.saveUser(user);
									System.out.println(SUCCESS);
								}else{
									//todo: failed
									out.writeUTF(FAIL);
									System.out.println(FAIL);
								}
							}else{
								//Illegal user
								System.out.println("Illegal User");
								out.writeUTF(ILLEGAL);
							}
						}
					}
				}
				clientsocket.close();
				System.out.println("Socket Closed");
			}catch(SocketTimeoutException e){
				System.out.println("Socket timed out");
				break;
			}catch(Exception e){
				e.printStackTrace();
				break;
			}
		}
	}
}
