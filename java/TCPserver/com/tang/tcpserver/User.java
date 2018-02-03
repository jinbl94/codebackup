package com.tang.tcpserver;

public class User{
	private String name;
	private String addinfo;
	private String password;
	private int count;
	private boolean invalidate=true;

	User(String Name,String Addinfo,String Password,int Count){
		name=Name;
		addinfo=Addinfo;
		password=Password;
		count=Count;
		invalidate=false;
	}

	String getName(){
		return name;
	}

	String getAddinfo(){
		return addinfo;
	}

	String getPassword(){
		return password;
	}

	int getCount(){
		return count;
	}

	boolean invalidate(){
		return invalidate;
	}

	void incCount(){
		count++;
	}
}
