# Introduction of Socket program in C program
## Protocol Name : UDP []

## UDP Header:
![image](https://user-images.githubusercontent.com/76644058/211717215-0fc4fe97-b752-411d-86c0-21bc3b5dbd27.png)

## Overview :
![image](https://user-images.githubusercontent.com/76644058/211717280-f7217069-639d-4d3f-b8b2-27a8c367e9ae.png)

#### UDP Server :  
    1.Create a UDP socket.<br>
    2.Bind the socket to the server address.<br>
    3.Wait until the datagram packet arrives from the client.<br>
    4.Process the datagram packet and send a reply to the client.<br>
    5.Go back to Step 3.<br>

#### UDP Client :  
    1.Create a UDP socket.<br>
    2.Send a message to the server.<br>
    3.Wait until response from the server is received.<br>
    4.Process reply and go back to step 2, if necessary.<br>
    5.Close socket descriptor and exit.<br>
