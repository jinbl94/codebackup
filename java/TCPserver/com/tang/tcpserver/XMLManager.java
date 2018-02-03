package com.tang.tcpserver;

import java.util.Random;
import java.io.*;
import javax.xml.parsers.*;
import javax.xml.transform.*;
import javax.xml.transform.dom.*;
import javax.xml.transform.stream.*;
import org.w3c.dom.*;
public class XMLManager{
	private String fileName;

	XMLManager(String FileName){
		fileName=FileName;
	}

	User readUser(){
		Element root,user,element;
		try{
			DocumentBuilderFactory dbf=DocumentBuilderFactory.newInstance();
			DocumentBuilder db=dbf.newDocumentBuilder();
			Document document=db.parse(new File(fileName));
			root=document.getDocumentElement();
			NodeList list=root.getElementsByTagName("user");
			user=(Element)list.item(0);
			String name=user.getElementsByTagName("name").item(0).getFirstChild().getNodeValue();
			String addinfo=user.getElementsByTagName("addinfo").item(0).getFirstChild().getNodeValue();
			String password=user.getElementsByTagName("password").item(0).getFirstChild().getNodeValue();
			int count=Integer.parseInt(user.getElementsByTagName("count").item(0).getFirstChild().getNodeValue());
			return new User(name,addinfo,password,count);
		}catch(Exception e){
			System.out.println("No user");
		}
		return null;
	}

	boolean saveUser(User mUser){
		try{
			DocumentBuilderFactory dbf=DocumentBuilderFactory.newInstance();
			DocumentBuilder db=dbf.newDocumentBuilder();
			Document document=db.newDocument();
			//build root node
			Element root,user,element;
			root=document.createElement("root");
			document.appendChild(root);
			user=document.createElement("user");
			root.appendChild(user);
			element=document.createElement("name");
			element.appendChild(document.createTextNode(mUser.getName()));
			user.appendChild(element);
			element=document.createElement("addinfo");
			element.appendChild(document.createTextNode(mUser.getAddinfo()));
			user.appendChild(element);
			element=document.createElement("password");
			element.appendChild(document.createTextNode(mUser.getPassword()));
			user.appendChild(element);
			element=document.createElement("count");
			element.appendChild(document.createTextNode(Integer.toString(mUser.getCount())));
			user.appendChild(element);
			TransformerFactory transformerFactory=TransformerFactory.newInstance();
			Transformer transformer=transformerFactory.newTransformer();
			transformer.setOutputProperty(OutputKeys.INDENT,"yes");
			DOMSource source=new DOMSource(document);
			StreamResult file=new StreamResult(new File(fileName));
			transformer.transform(source,file);
			return false;
		}catch(Exception e){
			e.printStackTrace();
		}
		return true;
	}
}
