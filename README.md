# SCL-Configuration-Tool


#IEC 61850 #mmslite

This project is a program for configuring SCL files in substations.

It was developed using Windows form.

Add.cpp and add.h have functions related to adding subscriptions. You must modify the file to change the value that is added or to change what is added.

The purpose of add_scl.cpp and add_cpp.h is to add space for scl_info related to the subscription. After you add space, you must insert the value through copy.

Convert.cpp and convert.h are related to the document conversion of scl_info. If you want to modify what is converted to an xml document in scl_info, you need to modify that file.

Copy.cpp and copy.h are related to content copying. Because scl_info is mostly pointers, we created a function that makes deep copies.

Find.cpp and find.h have functions to find the desired structure (such as scl_ln, scl_ld, etc.) in scl_info.

ngn.cpp contains a utility function.

remove.cpp is a function related to removal.
