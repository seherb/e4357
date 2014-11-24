import socket
import sys 
import urllib.request
import urllib.parse
import json
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('', 9999))
s.listen(1)
 
while True:
    conn, addr = s.accept()
    print ('Connected by', addr)
    while True:
        data = conn.recv(1024)
        if not data: break
        if data == bytes("1", encoding="UTF-8"):
           baseurl = "http://finance.yahoo.com/d/quotes.csv?s=FB&f=s0l1"
           yql_url= urllib.request.urlopen(baseurl).read()
           res1=str(yql_url, encoding="UTF-8")
           res1 = res1.translate(res1.maketrans("\"\r\n", "   ")) + '\n'
           baseurl = "http://finance.yahoo.com/d/quotes.csv?s=MSFT&f=s0l1"
           yql_url= urllib.request.urlopen(baseurl).read()
           res2=str(yql_url, encoding="UTF-8")
           res2 = res2.translate(res2.maketrans("\"\r\n", "   "))
           conn.sendall(bytes(res1+res2, encoding="UTF-8"))
        elif data == bytes("2", encoding="UTF-8"):
            baseurl = "https://query.yahooapis.com/v1/public/yql?"
            yql_query = "select item.condition from weather.forecast where woeid = 2487889"
            yql_url = baseurl + urllib.parse.urlencode({'q':yql_query}) + "&format=json"

            result = urllib.request.urlopen(yql_url ).read()
            res1 = str(result, encoding="UTF-8")
            data = json.loads(res1)

            str1 = data['query']['results']['channel']['item']['condition']['date'] + '\n'
            str2 = data['query']['results']['channel']['item']['condition']['text'] + '\n'
            str3 = data['query']['results']['channel']['item']['condition']['temp']
            conn.sendall(bytes(str1+str2+str3, encoding="UTF-8"))
        else:
            conn.sendall(bytes("1", encoding="UTF-8"))
    conn.close()