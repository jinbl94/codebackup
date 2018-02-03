package com.me.im;

import com.me.im.MyFrame;
public class Im
{
    public static void main(String args[])
    {
		if(args.length==0){
			System.out.println("Usage: Im recieve_port");
			System.exit(1);
		}
		System.out.println(Integer.parseInt(args[0]));
        MyFrame frame = new MyFrame(Integer.parseInt(args[0]));
    }
}
