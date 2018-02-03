#! /usr/bin/python 
import urllib.request,urllib.parse,urllib.error
#import socket
#from bs4 import BeautifulSoup
#import ssl
#import xml.etree.ElementTree as ET
import json

##ctx=ssl.create_default_context()
##ctx.check_hostname=False
##ctx.verify_mode=ssl.CERT_NONE


####parse data with json####
##url=input('Url - :')
##data=urllib.request.urlopen(url).read().decode()
##js=json.loads(data)
##comments=js['comments']
##nums=[]
##for i in range(len(comments)):
##	nums.append(int(comments[i]['count']))
##
##print('Result is:',sum(nums))


####google maps search api####
##serviceurl='https://maps.googleapis.com/maps/api/geocode/json?'
###serviceurl='http://py4e-data.dr-chuck.net/geojson?'
##
##while True:
##	address=input('Location: ')
##	if len(address)<1:break
##
##	url=serviceurl+urllib.parse.urlencode({'sensor':'false','address':address})
##
##	print('Retrieving',url)
##	uh=urllib.request.urlopen(url)
##	data=uh.read().decode()
##	print('Retrieved',len(data),'characters')
##
##	try:
##		js=json.loads(data)
##	except:
##		js=None
##
##	if not js or 'status' not in js or js['status']!='OK':
##		print('==== Failure To Retrieve ====')
##		print(data)
##		continue
##
##	place_id=js['results'][0]['place_id']
##	print('Place ID:',place_id)


####parsing xml data from the internet####
##url=input('Url - ')
##print('Retrieving',url)
##data=urllib.request.urlopen(url).read()
##tree=ET.fromstring(data)
##nums=tree.findall('.//count')
##
##lst=[]
##for i in range(len(nums)):
##	lst.append(int(nums[i].text))

##print('result is ',sum(lst))


####web crawler####
##url=input('Url: ')
##count=int(input('Count: '))
##position=int(input('Position: '))-1
##
##def geturl():
##	html=urllib.request.urlopen(url,context=ctx).read()
##	soup=BeautifulSoup(html,'html.parser')
##
##	tags=soup('a')
##	return tags[position].get('href',None)
##
##for i in range(count):
##	url=geturl()
##	print(url)


####socket programing in python####
##SITE='data.pr4e.org'
##PORT=80
##PAGE='intro-short.txt'
##cmd='GET http://{0}/{1} HTTP/1.0\r\n\r\n'.format(SITE,PAGE).encode()
##def GetData():
##	data=b''
##	mysocket=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
##	mysocket.connect((SITE,PORT))
##	mysocket.send(cmd)
##	while True:
##		package=mysocket.recv(512)
##		if(len(package)<1):
##			break
##		data+=package
##		print(package.decode())
##	mysocket.close()
##	return data
##GetData()
