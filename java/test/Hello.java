import java.util.Random;
import java.io.*;
import javax.xml.parsers.*;
import javax.xml.transform.*;
import javax.xml.transform.dom.*;
import javax.xml.transform.stream.*;
import org.w3c.dom.*;
public class Hello{
	private final static String USERFILE="temp.xml";

	public static void main(String[] args){
		XMLtest xmltest=new XMLtest(USERFILE);
		xmltest.saveUserToFile();
		xmltest.readUserFromFile();
	}
}

class XMLtest{
	private String fileName;

	XMLtest(String FileName){
		fileName=FileName;
	}

	void readUserFromFile(){
		Element root,user,element;
		try{
			DocumentBuilderFactory dbf=DocumentBuilderFactory.newInstance();
			DocumentBuilder db=dbf.newDocumentBuilder();
			Document document=db.parse(new File(fileName));
			root=document.getDocumentElement();
			NodeList list=root.getElementsByTagName("user");
			user=(Element)list.item(0);
			System.out.println("name: "+user.getElementsByTagName("name").item(0).getFirstChild().getNodeValue());
			System.out.println("addinfo: "+user.getElementsByTagName("addinfo").item(0).getFirstChild().getNodeValue());
			System.out.println("password: "+user.getElementsByTagName("password").item(0).getFirstChild().getNodeValue());
			System.out.println("count: "+Integer.parseInt(user.getElementsByTagName("count").item(0).getFirstChild().getNodeValue()));
		}catch(Exception e){
			e.printStackTrace();
		}
	}

	void saveUserToFile(){
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
			element.appendChild(document.createTextNode("username"));
			user.appendChild(element);
			element=document.createElement("addinfo");
			element.appendChild(document.createTextNode("additional_information"));
			user.appendChild(element);
			element=document.createElement("password");
			element.appendChild(document.createTextNode("userpassword"));
			user.appendChild(element);
			element=document.createElement("count");
			element.appendChild(document.createTextNode(Integer.toString(5)));
			user.appendChild(element);
			TransformerFactory transformerFactory=TransformerFactory.newInstance();
			Transformer transformer=transformerFactory.newTransformer();
			transformer.setOutputProperty(OutputKeys.INDENT,"yes");
			DOMSource source=new DOMSource(document);
			StreamResult file=new StreamResult(new File(fileName));
			transformer.transform(source,file);
			file=new StreamResult(System.out);
			transformer.transform(source,file);
		}catch(Exception e){
			e.printStackTrace();
		}
	}
}
