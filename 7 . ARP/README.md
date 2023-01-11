# Address Resolution Protocol (ARP)

- The acronym ARP stands for Address Resolution Protocol which is one of the most important protocols of the Network layer in the OSI model. 
  > Note: ARP finds the hardware address, also known as Media Access Control (MAC) address, of a host from its known IP address. 

## The important terms associated with ARP are: 
   1 . Reverse ARP <br>
   2 . Proxy ARP <br>
   3 . Inverse ARP <br>
 

- ARP Cache: After resolving the MAC address, the ARP sends it to the source where it is stored in a table for future reference. The subsequent communications can use the MAC address from the table
- ARP Cache Timeout: It indicates the time for which the MAC address in the ARP cache can reside
- ARP request: This is nothing but broadcasting a packet over the network to validate whether we came across the destination MAC address or not. 
      -  The physical address of the sender.<br>
      -  The IP address of the sender.<br>
      -  The physical address of the receiver is FF:FF:FF:FF:FF:FF or 1’s.<br>
      -  The IP address of the receiver<br>
- ARP response/reply: It is the MAC address response that the source receives from the destination which aids in further communication of the data. 

![image](https://user-images.githubusercontent.com/76644058/211500201-3f86fdb2-9ef0-4d44-8352-09f9db00f45f.png)

![image](https://user-images.githubusercontent.com/76644058/211500293-aad34f60-c5be-4f18-9975-c54c74860e9c.png)
