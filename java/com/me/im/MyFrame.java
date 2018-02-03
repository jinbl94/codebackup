package com.me.im;

import java.net.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.io.*;

public class MyFrame extends JFrame implements Runnable
{
    private JTextArea sendArea = new JTextArea(20,20);
    private JTextArea showArea = new JTextArea(10,20);
    private JButton sendButton = new JButton("Send");
    private MenuBar menuBar = new MenuBar();
    private Menu setMenu = new Menu("Setting");
    private Menu helpMenu = new Menu("Help");
    private MenuItem aboutItem = new MenuItem("About");    
    private MenuItem setItem = new MenuItem("Properties");
    private Thread thread = new Thread(this);
    private Config config = new Config();
    private JDialog dialog = new JDialog(this,"Properties",true);
    private int myPort;
    MyFrame(int in_myPort)
    {
        super("Our IM");
        setResizable(false);
        myPort = in_myPort;
        setItem.addActionListener(new SetDialog(dialog,this));
        aboutItem.addActionListener(new AboutDialog(this));
        initLayout();
        sendButton.addActionListener(new SendListener(this,sendArea,showArea,config));
        thread.start();
        addWindowListener(new WindowAdapter()
        {
            public void windowClosing(WindowEvent e)
            {
                System.exit(0);
            }
        });
    }
    void initLayout()
    {
        int w,h;
        w = 400;
        h = 500;
        setBounds(100,100,w,h);
        setVisible(true);
        setLayout(new GridLayout(3,1,10,15));
        JPanel jp1,jp2;
        jp1 = new JPanel();
        jp2 = new JPanel();
        JLabel jl1;
        jl1 = new JLabel("Log:");
        jp1.setLayout(null);
        jp1.add(jl1);
        jl1.setBounds(0,0,w,20);
        jp1.add(showArea);
        showArea.setBounds(0,30,w,h/3-20);
        JLabel jl2;
        jp2.setLayout(null);
        jl2 = new JLabel("Send:");
        jp2.add(jl2);
        jl2.setBounds(0,0,w,20);
        sendArea.setBounds(0,30,w,h/3-20);
        jp2.add(sendArea);
        JPanel jp3 = new JPanel();
        add(jp1);
        add(jp2);
        add(jp3);
        jp3.add(sendButton);
        setMenuBar(menuBar);
        menuBar.add(setMenu);
        menuBar.add(helpMenu);
        helpMenu.add(aboutItem);
        setMenu.add(setItem);
        dialog.setBounds(120,150,200,250);
        JLabel IPLabel = new JLabel("Peer IP");
        JLabel yourPortLabel = new JLabel("Peer Port");
        JLabel nameLabel = new JLabel("Hostname");
        JTextField IPTextField = new JTextField(15);
        JTextField yourPortTextField = new JTextField(8);
        JTextField nameTextField = new JTextField(15);
        IPTextField.setText("127.0.0.1");
        yourPortTextField.setText("9999");
        nameTextField.setText("test");
        
        dialog.setLayout(new GridLayout(4,2,10,10));
        dialog.add(IPLabel);
        dialog.add(IPTextField);
        dialog.add(yourPortLabel);
        dialog.add(yourPortTextField);
        dialog.add(nameLabel);
        dialog.add(nameTextField);
        dialog.add(new Panel());
        JButton sureButton = new JButton("Confirm");
        dialog.add(sureButton);
        sureButton.addActionListener(new SureListener(IPTextField,yourPortTextField,nameTextField,dialog,config));
    }
    public void run()
    {
        DatagramPacket dp = null;
        DatagramSocket ds = null;
        byte[] buf = new byte[1024];
        try
        {
            dp = new DatagramPacket(buf,buf.length);
            ds = new DatagramSocket(myPort);
            System.out.println("myport="+myPort);
        }
        catch (Exception e)
        {}
        while (true)
        {
            try
            {
                ds.receive(dp);
                int length = dp.getLength();
                InetAddress address = dp.getAddress();
                int port = dp.getPort();
                String message = new String(dp.getData(),0,length);
                showArea.append("Recieved:"+length+"\n");
                showArea.append("Source:"+address+"Port:"+port+"\n");
                showArea.append("Message:"+message+"\n");
            }
            catch (Exception e)
            {
            }
        }        
    }
}

//send
class SendListener implements ActionListener
{
    private JFrame MyFrame;
    private JTextArea sendArea;
    private JTextArea showArea;
    private Config config;
    SendListener(JFrame in_MyFrame, JTextArea in_sendArea, JTextArea in_showArea, Config in_config)
    {
        MyFrame = in_MyFrame;
        sendArea = in_sendArea;
        showArea =in_showArea;
        config = in_config;
        System.out.println("in_port:"+config.getyourPort());
        MyFrame.validate();
    }

    public void actionPerformed(ActionEvent e)
    {
        System.out.println("You clicked \"Send\"");
        byte[] buf = sendArea.getText().trim().getBytes();
        try
        {
            InetAddress address = InetAddress.getByName(config.getIP());
            DatagramPacket dp = new DatagramPacket(buf,buf.length,address,Integer.parseInt(config.getyourPort()));
            DatagramSocket ds = new DatagramSocket();
            showArea.append("Destination:"+dp.getAddress()+"\n");
            showArea.append("Port:"+dp.getPort()+"\n");
            showArea.append("Lenght"+dp.getLength()+"\n");
            ds.send(dp);
        }
        catch (Exception ee) {}
    }
}

//setting
class SetDialog implements ActionListener
{
    private JDialog dialog;
    private JFrame frame;
    SetDialog(JDialog in_dialog,JFrame parent)
    {
        dialog = in_dialog;
        frame = parent;
    }
    public void actionPerformed(ActionEvent e)
    {
        dialog.validate();
        int x = frame.getX();
        int y = frame.getY();
        dialog.setBounds(x+50,y+50,200,250);
        dialog.setVisible(true);
    }
}
//about
class AboutDialog extends JDialog implements ActionListener
{
    private JFrame frame;
    private JLabel jl = new JLabel("This is our IM program!");
    AboutDialog(JFrame parent)
    {
        frame = parent;
        add(jl);
    }
    public void actionPerformed(ActionEvent e)
    {
        validate();
        int x = frame.getX();
        int y = frame.getY();
        setBounds(x+50,y+50,200,250);
        setVisible(true);
    }
}
//confirm
class SureListener implements ActionListener
{
    JTextField IPTextField;
    JTextField yourPortTextField;
    JTextField nameTextField;
    private Dialog dialog;
    private Config config;
    
    SureListener(JTextField in_IPTextField,JTextField in_yourPortTextField,JTextField in_nameTextField,JDialog in_dialog,Config in_config)
    {
        IPTextField = in_IPTextField;
        yourPortTextField = in_yourPortTextField;
        nameTextField = in_nameTextField;
        dialog = in_dialog;
        config = in_config;
    }
    public void actionPerformed(ActionEvent e)
    {
        config.set(IPTextField.getText(),yourPortTextField.getText(),nameTextField.getText());
        System.out.println("config:yourPort:"+config.getyourPort());
        dialog.setVisible(false);
    }
}
//properties
class Config
{
    private String IP="127.0.0.1";
    private String yourPort="9999";
    private String name="test";

    public void set(String in_IP, String in_yourPort,String in_name)
    {
        IP = in_IP;
        yourPort = in_yourPort;
        name = in_name;
    }
    public String getIP()
    {
        return IP;
    }
    public String getyourPort()
    {
        return yourPort;
    }
    public String getName()
    {
        return name;
    }
}
