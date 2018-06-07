# Warehouse-Management
A MFC based warehouse management system.

## Introduction
The little system is designed to realize somehow intelligent management of warehouse. With the imagine that all of the parts are equiped with a barcode label, by scaaning this label we could get the detail information of the part and its position on the shelve. Moreover, the position could be inspired with visualation.  
The system are based on database sothat it is possible to communicate with other underlying hardware. Database can also improve the system's extension posibility.

## GUI
The program initialize itself with the GUI below.  
![image](https://github.com/wenyi1994/Warehouse-Management/blob/master/pics/GUI.png)  
The Editbox on topleft could receive barcode or QRcode from scanner. By clicking "Query" button (it is automated with using custmized scanner) the detail information of Part are shown.  
![image](https://github.com/wenyi1994/Warehouse-Management/blob/master/pics/Part.png)  
If the system find that this is a barcode / QRcode from order, it will prompt which parts the order need and their position on the shelves.  
![image](https://github.com/wenyi1994/Warehouse-Management/blob/master/pics/Order.png)  
If the system find that the scanned barcode or QRcode is not in the database, it will provide a dialog for user to decide, whether the part / order should be added in the database or not.  
![image](https://github.com/wenyi1994/Warehouse-Management/blob/master/pics/Add.png)
