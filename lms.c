/***************************************************************************************/ 
/*                              C Programming Project                                  */
/*                    MEDKS Library Management System FINAL PROJECT                    */
/***************************************************************************************/ 



/***************************************************************************************/ 
/*                       Default Global Variables and Constants                        */
/***************************************************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "encrypt.h"
#define LIBRARYFILE "lmslibrary.txt"
#define USERFILE "lmsusers.txt"
#define MAXITEMS 1000
#define MAXSHELFLOCATION 10000
#define MAXREQUESTS 1000
#define MAXUSERS 100
#define MAXITEMLENGTH 41
#define MAXITEMQTY 1000
#define MAXITEMPRICE 100000.00
#define MAXIDLENGTH 15
#define MINIDLENGTH 8
#define MAXBOOKSREQUESTED 3
#define MAXBOOKSLOANED 3
#define ADMIN "ADMIN"
#define GUEST "GUEST"

int NumUsers = 0;
int NumItems = 0;
int NumRequests = 0;
int LastRequestID = 0;
int LastUserID = 0;
int LastItemID = 0;
int CurrentUserID = 0;
int CurrentUserType = 0; 

struct request_record
{
 int id, userid, itemid;
};

struct request_record requestlist[MAXREQUESTS];  //this array contains a list of all borrowing requests

struct item_record
{
 char title[MAXITEMLENGTH], author[MAXITEMLENGTH], subject[MAXITEMLENGTH], isbn[MAXITEMLENGTH], format[MAXITEMLENGTH]; 
 int itemid, location, qty;
 float price;
}; // creates item_record custom data type

struct item_record library[MAXITEMS]; //this array contains all library content 

struct user_record
{
 char name[MAXIDLENGTH], password[MAXIDLENGTH], type[MAXIDLENGTH];
 int id, nbloaned, nbrequested, reqid[MAXBOOKSREQUESTED], booksloaned[MAXBOOKSLOANED], booksrequested[MAXBOOKSREQUESTED]; 
}; // creates user_record custom data type

struct user_record user[MAXUSERS];  //this array contains all user account information 

/***************************************************************************************/ 
/*                  Function to initialize library with test data                      */
/***************************************************************************************/ 

void loadTestLibrary() {
  library[1].itemid = 1;
  library[1].qty = 12;
  library[1].location = 888;
  library[1].price = 9.99;
  strcpy(library[1].title,    "Atlas");
  strcpy(library[1].author,   "The Score");
  strcpy(library[1].subject,  "music");
  strcpy(library[1].isbn,     "6739820817");
  strcpy(library[1].format,   "CD");

  library[2].itemid = 2;
  library[2].qty = 8;
  library[2].location = 777;
  library[2].price = 11.00;
  strcpy(library[2].title,   "Harry Potter");
  strcpy(library[2].author,  "JK Rowling");
  strcpy(library[2].subject, "fiction");
  strcpy(library[2].isbn,    "2745394572");
  strcpy(library[2].format,   "hardcover");

  library[3].itemid = 3;
  library[3].qty = 7;
  library[3].location = 321;
  library[3].price = 5.99;
  strcpy(library[3].title,   "Animal Farm");
  strcpy(library[3].author,  "George Orwell");
  strcpy(library[3].subject, "fiction");
  strcpy(library[3].isbn,    "9780241196");
  strcpy(library[3].format,   "paperback");
  
  library[4].itemid = 4;
  library[4].qty = 1;
  library[4].location = 101;
  library[4].price = 14.99;
  strcpy(library[4].title,   "Fahrenheit 451");
  strcpy(library[4].author,  "Ray Bradbury");
  strcpy(library[4].subject, "fiction");
  strcpy(library[4].isbn,    "8821407053");
  strcpy(library[4].format,   "hardcover");

  library[5].itemid = 5;
  library[5].qty = 17;
  library[5].location = 54;
  library[5].price = 17.99;
  strcpy(library[5].title,   "Calculus for Dummies");
  strcpy(library[5].author,  "Mark Ryan");
  strcpy(library[5].subject, "textbook");
  strcpy(library[5].isbn,    "9780764524");
  strcpy(library[5].format,   "paperback");

  library[6].itemid = 6;
  library[6].qty = 9;
  library[6].location = 985;
  library[6].price = 3.99;
  strcpy(library[6].title,   "Art of War");
  strcpy(library[6].author,  "Sun Tzu");
  strcpy(library[6].subject, "non-fiction");
  strcpy(library[6].isbn,    "9781982530");
  strcpy(library[6].format,   "hardcover");

  library[7].itemid = 7;
  library[7].qty = 15;
  library[7].location = 762;
  library[7].price = 7.99;
  strcpy(library[7].title,   "Cleopatra");
  strcpy(library[7].author,  "The Lumineers");
  strcpy(library[7].subject, "music");
  strcpy(library[7].isbn,    "225830971");
  strcpy(library[7].format,   "CD");

  library[8].itemid = 8;
  library[8].qty = 3;
  library[8].location = 66;
  library[8].price = 4.99;
  strcpy(library[8].title,   "Weapons of Math Destruction");
  strcpy(library[8].author,  "Cathy O'Neil");
  strcpy(library[8].subject, "non-fiction");
  strcpy(library[8].isbn,    "4782938871");
  strcpy(library[8].format,   "paperback");

  library[9].itemid = 9;
  library[9].qty = 5;
  library[9].location = 151;
  library[9].price = 24.99;
  strcpy(library[9].title,   "Die Hard Series");
  strcpy(library[9].author,  "20th Century Studios");
  strcpy(library[9].subject, "film");
  strcpy(library[9].isbn,    "8938094712");
  strcpy(library[9].format,   "CD");

library[10].itemid = 10;
  library[10].qty = 12;
  library[10].location = 413;
  library[10].price = 7.99;
  strcpy(library[10].title,   "A Night at the Opera");
  strcpy(library[10].author,  "Queen");
  strcpy(library[10].subject, "music");
  strcpy(library[10].isbn,    "3303981343");
  strcpy(library[10].format,   "CD");
  
  NumItems = 10;
  LastItemID = 10;
}


/***************************************************************************************/ 
/*              Function to initialize user accounts with test data                    */
/***************************************************************************************/ 

void loadTestUsers() {
  strcpy(user[1].name,     "testname1");
  strcpy(user[1].password, "testpass1");
  strcpy(user[1].type,     ADMIN);
  user[1].id = 1;
  user[1].nbloaned = 0;
  user[1].nbrequested = 0;

  strcpy(user[2].name,     "testname2");
  strcpy(user[2].password, "testpass2");
  strcpy(user[2].type,     GUEST);
  user[2].id = 2;
  user[2].nbloaned = 1;
  user[2].booksloaned[1] = 1;
  user[2].nbrequested = 1;
  user[2].reqid[1] = 1;
  user[2].booksrequested[1] = 1;

  strcpy(user[3].name,     "testname3");
  strcpy(user[3].password, "testpass3");
  strcpy(user[3].type,     GUEST);
  user[3].id = 3;
  user[3].nbloaned = 1;
  user[3].booksloaned[1] = 2;
  user[3].nbrequested = 2;
  user[3].reqid[1] = 2;
  user[3].reqid[2] = 3;
  user[3].booksrequested[1] = 3;
  user[3].booksrequested[2] = 4;
  
  strcpy(user[4].name,     "testname4");
  strcpy(user[4].password, "testpass4");
  strcpy(user[4].type,     GUEST);
  user[4].id = 4;
  user[4].nbloaned = 0;
  user[4].nbrequested = 1;
  user[4].reqid[1] = 4;
  user[4].booksrequested[1] = 4;
  
  requestlist[1].id = 1;
  requestlist[1].userid = 2;
  requestlist[1].itemid = 1;
  //requestlist[1].time = 14;
  
  requestlist[2].id = 2;
  requestlist[2].userid = 3;
  requestlist[2].itemid = 3;
  //requestlist[2].time = 28;
  
  requestlist[3].id = 3;
  requestlist[3].userid = 3;
  requestlist[3].itemid = 4;
  //requestlist[3].time = 7;
  
  requestlist[4].id = 4;
  requestlist[4].userid = 4;
  requestlist[4].itemid = 4;
  //requestlist[4].time = 21;
  
  NumUsers = 4;
  NumRequests = 4;
  LastRequestID = 4;
  LastUserID = 4;
}


/***************************************************************************************/ 
/*               Function to read user account list from external file                 */
/***************************************************************************************/ 

void readUserFile() {
   FILE *userfile;
   int i, j;
   
   //printf("\nEntering read, Total Requests = %d Last Request ID = %d\n", NumRequests, LastRequestID);
   
   LastUserID = 0;
   LastRequestID = 0;
   
   //initialize 'user' array
   
   for (i = 1; (i <= MAXUSERS); i++) {
	  strcpy(user[i].name,     "");
      strcpy(user[i].password, "");
      strcpy(user[i].type,     "");
      user[i].id = 0;
      user[i].nbloaned = 0;
	  user[i].nbrequested = 0;
	  for (j = 1; (j <= MAXBOOKSREQUESTED); j++) {
		user[i].reqid[j] = 0;
		user[i].booksrequested[j] = 0;
	  }
	  for (j = 1; (j <= MAXBOOKSLOANED); j++) {
		user[i].booksloaned[j] = 0;
	  }
   }

   //Open user account file
   
   NumRequests = 0;

   if (createStatus() == 1) {
	   //printf("Status = 1, won't decrypt non-encrypted data");
   } else if (createStatus() == 0) {
	   //printf("Status = 0, encrypted user data would be decrypted here");
	   decrypt(USERFILE);
   }

   userfile = fopen(USERFILE, "r");
   if (userfile == NULL) {
      printf("\nWarning - Unable to read USERFILE");
	  printf("\n          Initializing user accounts with test data");
	  loadTestUsers();
	}
	
	//read user account file and store in 'user' array
	else {
	  NumUsers = 1;
	  while (fread(&user[NumUsers], sizeof(struct user_record), 1, userfile)) {
		NumUsers = NumUsers + 1;
		if (NumUsers > MAXUSERS) {
		  printf("\nError - number of external user account records exceeds maximum.");
		  printf("\n        Some user account information will not be accessible.   ");
		  NumUsers = NumUsers - 1;
		  fclose(userfile);
		  break;
	    }
	  }
	  NumUsers = NumUsers -1;
	  for (i = 1; (i <= NumUsers); i++) {
		 if (user[i].id > LastUserID) {
			 LastUserID = user[i].id;
		 }
	  }
	  
	  // store borrow requests in 'request' array for faster access
		  
	  for (i = 1; (i <= NumUsers); i++) {
		for (j = 1; (j <= user[i].nbrequested); j++) {
		  NumRequests = NumRequests + 1;
		  requestlist[NumRequests].userid = user[i].id;
		  requestlist[NumRequests].id = user[i].reqid[j];
		  requestlist[NumRequests].itemid = user[i].booksrequested[j];
		  //printf("\nIn loop, reqid = %d\n", user[i].reqid[j]);
		  if (user[i].reqid[j] > LastRequestID) {
			 LastRequestID = user[i].reqid[j];
		  }
	    }
	  }
	  fclose(userfile);
   }
}


/***************************************************************************************/ 
/*               Function to write user account list from external file                */
/***************************************************************************************/ 

void writeUserFile() {
   FILE *userfile;
   char name[MAXIDLENGTH], password[MAXIDLENGTH], type[MAXIDLENGTH];
   int i, id, nbloaned, loanid1, loanid2, loanid3, loanid4, loanid5, nbrequested, reqid1, reqid2, reqid3, reqid4, reqid5;		

   //Open user account file

	if (createStatus() == 1) {
		//printf("Status = 1, won't decrypt pre-encrypted file");
	} else if (createStatus() == 0) {
		//printf("Status = 0, encrypted file would be decrypted here");
		decrypt(USERFILE);
	}

   userfile = fopen(USERFILE, "w");
   if (userfile == NULL) {
      printf("\nError - Unable to write to USERFILE                ");
	  printf("\n        User account information will not be stored");
   } 
   // write 'user' array records to external file
   else {
	 for (i = 1; (i <= NumUsers); i++) {
	   fwrite(&user[i], sizeof(struct user_record), 1, userfile);
	 }
   fclose(userfile);
   encrypt(USERFILE);
   }
}


/***************************************************************************************/ 
/*               Function to read library records from external file                   */
/***************************************************************************************/ 
 
void readLibraryFile() {
   FILE *libraryfile;
   char title[MAXITEMLENGTH], author[MAXITEMLENGTH], subject[MAXITEMLENGTH], isbn[MAXITEMLENGTH], format[MAXITEMLENGTH];
   int i, itemid, qty, location;
   float price;
   
   //Open library file
   
   LastItemID = 0;
   
   libraryfile = fopen(LIBRARYFILE, "r");
   if (libraryfile == NULL) {
      printf("\nWarning - Unable to read LIBRARYFILE.        ");
 	  printf("\n          Initializing library with test data");
 	  loadTestLibrary();
	  fclose(libraryfile);
   }
   // read library file and store in 'library' array
   else {  
	  NumItems = 1;
	  while (fread(&library[NumItems], sizeof(struct item_record), 1, libraryfile)) {
		NumItems = NumItems + 1;
		if (NumItems > MAXITEMS) {
	 	  printf("\nError - number of external library records exceeds maximum");
		  printf("\n        Some library information will not be accessible   ");
		  NumItems = NumItems - 1;
		  fclose(libraryfile);
		  break;
	    }
	  }
	  NumItems = NumItems -1;
	  for (i = 1; (i <= NumItems); i++) {
		 if (library[i].itemid > LastItemID) {
			 LastItemID = library[i].itemid;
		 }
	  }
	  fclose(libraryfile);
   }
}


/***************************************************************************************/ 
/*               Function to write library records to external file                    */
/***************************************************************************************/ 
 
void writeLibraryFile() {
   FILE *libraryfile;
   char title[MAXITEMLENGTH], author[MAXITEMLENGTH], subject[MAXITEMLENGTH], isbn[MAXITEMLENGTH], format[MAXITEMLENGTH];
   int i, itemid, location, qty;
   float price;

   //Open library file
   
   libraryfile = fopen(LIBRARYFILE, "w");
   if (libraryfile == NULL) {
      printf("\nError - Unable to write to LIBRARYFILE      ");
	  printf("\n        Library records will not be stored  ");
	  fclose(libraryfile);
   }
   // write 'library' array records to external file
   else {   
	 for (i = 1; (i <= NumItems); i++) {
	   fwrite(&library[i], sizeof(struct item_record), 1, libraryfile);
	 }
   	fclose(libraryfile);
   }
}

/***************************************************************************************/ 
/*       Function to check if library item data is formattted correctly                */
/***************************************************************************************/ 

int checkLibraryItemDataFormat(char format[MAXITEMLENGTH], char isbn[MAXITEMLENGTH], int location, int qty, float price) {
	
	int i, error, match, NumFormats = 9;
    char FormatList[9][MAXITEMLENGTH] = {"hardcover", "paperback", "journal", "dissertation", "magazine", "newspaper", "audiobook", "ebook", "CD"};
	
	error = 0;
	
	// check format	
	
	match = 0;
	for (i=0; (i <= NumFormats); i++) {
       if (strcmp(FormatList[i], format) == 0) {
		 match = 1;
		 break;
	   }
    }
	if (match == 0) {
	  error = 1;
	  printf("\nError - Invalid FORMAT entered");
	}
	
	// check ISBN 
	
	if (strcmp(isbn, "NA") != 0) {
	  if (strlen(isbn) != 10) {
		error = 1;
		printf("\nError - ISBN format is invalid");
	  }
	  else {
	     for (i=0; i<=9; i++) {
	        if (isdigit(isbn[i]) == 0) {
			  error = 1;
		      printf("\nError - ISBN format is invalid");
			  break;
			}
		 }
	  }
	}
	
	// check shelf location 
	
	if (location < 1 || location > MAXSHELFLOCATION) {
	  error = 1;
	  printf("\nError - Invalid SHELF LOCATION entered");
	}
	
	// check quantity	
	 
	if (qty < 1 || qty > MAXITEMQTY) {
	  error = 1;
	  printf("\nError - Invalid QUANTITY entered");
	}

    // check price
	
	if (price < 0.0 || price > MAXITEMPRICE) {
	   error = 1;
	   printf("\nError - Invalid PRICE entered");
	}
	
    return(error);
}


/***************************************************************************************/ 
/*                     Function to check that item inputs are valid                    */
/***************************************************************************************/ 

int checkItemInputs (char title[MAXITEMLENGTH], char author[MAXITEMLENGTH], char format[MAXITEMLENGTH], char isbn[MAXITEMLENGTH], int location, int qty, int price)

{
	int i, error, match, NumFormats = 9;
    char FormatList[9][MAXITEMLENGTH] = { "hardcover", "paperback", "journal", "dissertation", "magazine", "newspaper", "audiobook", "ebook", "CD"};

	error = 0;
	
	// check if there is available spacein the 'library' array to add a new item
	
	if (NumItems == MAXITEMS) {
	  error = 1;
	  printf("\nError - library database is full and cannot accept any new items");
	}
	
	// check for formatting errors
	
	error = checkLibraryItemDataFormat(format, isbn, location, qty, price);
	
	// check for duplicate SHELF LOCATION
		
	for (i=1; (i <= NumItems); i++) {
	   if (library[i].location == location) {
		 error = 1;
		 printf("\nError - An item with this SHELF LOCATION already exists in the library");
		 break;
	   }
	}
	
	// check for duplicate ISBN
	
	if (strcmp(isbn, "NA") != 0) {
	  for (i=1; (i <= NumItems); i++) {
	    if (strcmp(library[i].isbn, isbn) == 0) {
		  error = 1;
		  printf("\nError - An item with this ISBN already exists in the library");
		  break;
	    }
	  }
	}
	
	// check for duplicate TITLE, AUTHOR and FORMAT combination
	
	for (i=1; (i <= NumItems); i++) {
	  if (strcmp(library[i].title, title) == 0 && strcmp(library[i].author, author) == 0 && strcmp(library[i].format, format) == 0) {
		 error = 1;
		 printf("\nError - An item with this combination of TITLE, AUTHOR and FORMAT already exists in the library");
		 break;
	  }
	}
	
    return(error);
}


/***************************************************************************************/ 
/*                     Function to to check that item edits are valid                  */
/***************************************************************************************/ 

int checkItemEdits (int itemid, char title[MAXITEMLENGTH], char author[MAXITEMLENGTH], char format[MAXITEMLENGTH], char isbn[MAXITEMLENGTH], int location, int qty, float price)

{
	int i, error, match, NumFormats = 9;
    char FormatList[9][MAXITEMLENGTH] = { "hardcover", "paperback", "journal", "dissertation", "magazine", "newspaper", "audiobook", "ebook", "CD"};

	error = 0;
	
	// check for formatting errors
	
	error = checkLibraryItemDataFormat(format, isbn, location, qty, price);
	
	// check for duplicate shelf location 

    for (i=1; (i <= NumItems); i++) {
	  if (library[i].itemid != itemid && library[i].location == location) {
        error = 1;
		printf("\nError - An item with this SHELF LOCATION already exists in the library");
		break;
	  }
    }
	
	// check for duplicate ISBN
	
	if (strcmp(isbn, "NA") != 0) {
	  for (i=1; (i <= NumItems); i++) {
	    if (library[i].itemid != itemid && strcmp(library[i].isbn, isbn) == 0) {
	      error = 1;
		  printf("\nError - An item with this ISBN already exists in the library");
		  break;
		}
	  }
	}
	
	// check for duplicate title, author, format combination
	
	for (i=1; (i <= NumItems); i++) {
	  if (library[i].itemid != itemid && strcmp(library[i].title, title) == 0 && strcmp(library[i].author, author) == 0 && strcmp(library[i].format, format) == 0) {
		 error = 1;
		 printf("\nError - An item with this combination of TITLE, AUTHOR and FORMAT already exists in the library");
		 break;
	  }
	}
	
    return(error);
}

/***************************************************************************************/ 
/*                     Function to add item to library                                 */
/***************************************************************************************/ 

static void addItemtoLibrary() {	
    char yesno, title[MAXITEMLENGTH], author[MAXITEMLENGTH], subject[MAXITEMLENGTH], isbn[MAXITEMLENGTH], format[MAXITEMLENGTH], strlocation[MAXITEMLENGTH], strqty[MAXITEMLENGTH], strprice[MAXITEMLENGTH];
    int itemid, location, qty, i, j, error, ncounter, tryagain;
    float price;

    printf("\n");
	printf("\n");
    printf("********************************************\n");
    printf("***     Add item to library              ***\n");  
    printf("********************************************\n");
	printf("\n"); 
	
	// Get user inputs
	
	tryagain = 1;
	while (tryagain == 1)  {
	  printf("\nEnter TITLE (max of %d characters): ", MAXITEMLENGTH-1);
	  fflush(stdin);
	  fgets(title, MAXITEMLENGTH, stdin);
	  title[strlen(title) - 1] = '\0';           // remove the line break character
	
	  printf("\nEnter AUTHOR (max of %d characters): ", MAXITEMLENGTH-1);
	  fflush(stdin);
	  fgets(author, MAXITEMLENGTH, stdin);
      author[strlen(author) - 1] = '\0';      // remove the line break character
	
	  printf("\nEnter SUBJECT (max of %d characters): ", MAXITEMLENGTH-1);
	  fflush(stdin);
	  fgets(subject, MAXITEMLENGTH, stdin);
	  subject[strlen(subject) - 1] = '\0';    // remove the line break character
	
	  printf("\nEnter ISBN (unique 10 digit identfier or NA): ");
	  fflush(stdin);
	  fgets(isbn, MAXITEMLENGTH, stdin);
	  isbn[strlen(isbn) - 1] = '\0';          // remove the line break character
	
	  printf("\nEnter FORMAT (hardcover, paperback, journal, dissertation, magazine, newspaper, audiobook, ebook, CD): ");
	  fflush(stdin);
	  fgets(format, MAXITEMLENGTH, stdin);
	  format[strlen(format) - 1] = '\0';      // remove the line break character
	  
	  printf("\nEnter SHELF LOCATION (1 - %d): ", MAXSHELFLOCATION);
	  fflush(stdin);
	  fgets(strlocation, MAXITEMLENGTH, stdin);
	  strlocation[strlen(strlocation) - 1] = '\0';      // remove the line break character
	  location = atoi(strlocation);                     // convert string to integer
	
	  printf("\nEnter QUANTITY (1 - %d): ", MAXITEMQTY);
	  fflush(stdin);
	  fgets(strqty, MAXITEMLENGTH, stdin);
	  strqty[strlen(strqty) - 1] = '\0';      // remove the line break character
	  qty = atoi(strqty);                     // convert string to integer
	  
	  printf("\nEnter PRICE: ($1 - $%.2f): ", MAXITEMPRICE);
	  fflush(stdin);
	  fgets(strprice, MAXITEMLENGTH, stdin);
	  strprice[strlen(strprice) - 1] = '\0';      // remove the line break character
	  price = atof(strprice);                     // convert string to integer
	
	// Ask user to confirm inputs
	
	  printf("\n");
	  printf("TITLE          = %s \n",    title);
	  printf("AUTHOR         = %s \n",    author);
	  printf("SUBJECT        = %s \n",    subject);
	  printf("ISBN           = %s \n",    isbn);
	  printf("FORMAT         = %s \n",    format);
	  printf("SHELF LOCATION = %d \n",    location);
	  printf("QUANTITY       = %d \n",    qty);
	  printf("PRICE          = $%.2f \n", price);
	  printf("\n");
	  
	  yesno = ' ';
	  printf("Is this correct? (y/n): ");
	  fflush(stdin);
	  scanf("%c", &yesno);
      if (yesno == 'Y' || yesno == 'y') {
		 tryagain = 0;
		 if (checkItemInputs(title, author, format, isbn, location, qty, price) ==  0) {
			 
		   // create new library record for this item
		   
		   NumItems = NumItems + 1;
		   LastItemID = LastItemID + 1;
		   library[NumItems].itemid = LastItemID;
           library[NumItems].qty = qty;
           library[NumItems].location = location;
           library[NumItems].price = price;
           strcpy(library[NumItems].title,   title);
           strcpy(library[NumItems].author,  author);
           strcpy(library[NumItems].subject, subject);
           strcpy(library[NumItems].isbn,    isbn);
           strcpy(library[NumItems].format,  format);
		   printf("Item has been successfully added to the library");
		 }
	  }
	  else {
		 yesno = ' ';
		 tryagain = 0;
		 printf("Do you want to try again? (y/n): ");
	     fflush(stdin);
	     scanf("%c", &yesno);
         if (yesno == 'Y' || yesno == 'y') {
		    tryagain = 1;
		 }
	  }
	}	  
}
	

/***************************************************************************************/ 
/*                     Function to delete item from library                            */
/***************************************************************************************/ 

static void deleteItemfromLibrary() {	

    int i, j, itemid, error, ncounter; 

    printf("\n");
	printf("\n");
    printf("********************************************\n");
    printf("***     Delete item from library         ***\n");  
    printf("********************************************\n");
	printf("\n"); 
    
	printf("\nEnter Item ID Number:");
	scanf("%d", &itemid);
	
	error = 1;
	for (i=1; (i <= NumItems); i++) {
		if (library[i].itemid == itemid) {
		  error = 0;
		  break;
	    }
	}
	if (error == 1) {
		printf("Error - invalid Item ID entered");
	}	
	else {
		
	   // remove item from library
	   
	   ncounter = 0;
	   for (i=1; (i <= NumItems); i++) {
	      if (library[i].itemid != itemid) {
		      ncounter = ncounter + 1;
	          library[ncounter] = library[i];
	      }
	   }
       NumItems = ncounter;
	   
	   // remove item from request list
	   
	   
	   ncounter = 0;
	   for (i=1; (i <= NumRequests); i++) {
	      if (requestlist[i].itemid != itemid) {
		      ncounter = ncounter + 1;
	          requestlist[ncounter] = requestlist[i];	
	      }
	   }
       NumRequests = ncounter;   
	   
	   // remove item from user records
	   
	   for (i=1; (i <= NumUsers); i++) { 
		  
		  ncounter = 0;
	      for (j=1; (j <= user[i].nbrequested); j++) {
	         if (user[i].booksrequested[j] != itemid) {
		        ncounter = ncounter + 1;
				user[i].reqid[ncounter] = user[i].reqid[j];
	            user[i].booksrequested[ncounter] = user[i].booksrequested[j];
	      }
	     }
         user[i].nbrequested = ncounter;
		 
		 ncounter = 0;
	      for (j=1; (j <= user[i].nbloaned); j++) {
	         if (user[i].booksloaned[j] != itemid) {
		        ncounter = ncounter + 1;
	            user[i].booksloaned[ncounter] = user[i].booksloaned[j];
	      }
	     }
         user[i].nbloaned = ncounter;
	   }
	   
	   printf("Item has been successfully deleted");
	}	
}

/***************************************************************************************/ 
/*                     Function to edit library item                                   */
/***************************************************************************************/ 

static void editLibraryItem() {	
    char yesno, title[MAXITEMLENGTH], author[MAXITEMLENGTH], subject[MAXITEMLENGTH], isbn[MAXITEMLENGTH], format[MAXITEMLENGTH], strlocation[MAXITEMLENGTH], strqty[MAXITEMLENGTH], strprice[MAXITEMLENGTH]; 
    int i, itemid, location, qty, tryagain, nrec;
    float price;

    printf("\n");
	printf("\n");
    printf("********************************************\n");
    printf("***         Edit library item            ***\n");  
    printf("********************************************\n");
	printf("\n"); 
	
	// Get user inputs
	
	tryagain = 1;
	while (tryagain == 1)  {
	  printf("\nEnter Library Item ID: ");
	  fflush(stdin);
	  scanf("%d", &itemid);
	  
	  nrec = 0;
	  for (i=1; i<=NumItems; i++) {
		 if (library[i].itemid == itemid) {
		    nrec = i;
			break;
		 }
	  }
	  if (nrec == 0) {
	    yesno = ' ';
	    printf("Error = Library Item ID is invalid.  Do you want to try again? (y/n): ");
	    fflush(stdin);
	    scanf("%c", &yesno);
        if (yesno != 'Y' && yesno != 'y') {
		   tryagain = 0;
		}
	  }
	  else {
	    printf("\n");
		printf(" ID       TITLE                AUTHOR               SUBJECT              ISBN        FORMAT           LOC     QTY     PRICE\n");
	    printf("\n%-5i     %-20.20s %-20.20s %-20.20s %-10.10s  %-15.15s  %-5i   %-5i   $%9.2f", library[itemid].itemid, library[itemid].title, library[itemid].author, library[itemid].subject, library[itemid].isbn, library[itemid].format, library[itemid].location, library[itemid].qty, library[itemid].price);
	    printf("\n");
	
	    printf("\nEnter new TITLE then press Enter, or just press Enter alone for no change: ");
	    fflush(stdin);
	    fgets(title, MAXITEMLENGTH, stdin);
        title[strlen(title) - 1] = '\0';                 // remove the line break character
	  
	    printf("\nEnter new AUTHOR then press Enter, or just press Enter alone for no change: ");
	    fflush(stdin);
	    fgets(author, MAXITEMLENGTH, stdin);
        author[strlen(author) - 1] = '\0';               // remove the line break character
	
	    printf("\nEnter new SUBJECT then press Enter, or just press Enter alone for no change: ");
	    fflush(stdin);
	    fgets(subject, MAXITEMLENGTH, stdin);
	    subject[strlen(subject) - 1] = '\0';             // remove the line break character
	
	    printf("\nEnter new ISBN then press Enter, or just press Enter alone for no change: ");
	    fflush(stdin);
	    fgets(isbn, MAXITEMLENGTH, stdin);
	    isbn[strlen(isbn) - 1] = '\0';                   // remove the line break character
	
	    printf("\nEnter new FORMAT then press Enter, or just press Enter alone for no change: ");
	    fflush(stdin);
	    fgets(format, MAXITEMLENGTH, stdin);
	    format[strlen(format) - 1] = '\0';               // remove the line break character
	  
	    printf("\nEnter new SHELF LOCATION then press Enter, or just press Enter alone for no change: ");
		fflush(stdin);
		fgets(strlocation, MAXITEMLENGTH, stdin);
		strlocation[strlen(strlocation) - 1] = '\0';     // remove the line break character
	
	    printf("\nEnter new QUANTITY then press Enter, or just press Enter alone for no change: ");
		fflush(stdin);
		fgets(strqty, MAXITEMLENGTH, stdin);
		strqty[strlen(strqty) - 1] = '\0';              // remove the line break character
	  
	    printf("\nEnter new PRICE then press Enter, or just press Enter alone for no change: ");
		fflush(stdin);
		fgets(strprice, MAXITEMLENGTH, stdin);
		strprice[strlen(strprice) - 1] = '\0';          // remove the line break character
	
	    // Ask user to confirm inputs, mark editted fields with an asterisk
	
	    printf("\n");
		if (strcmp(title, "") != 0) {
		  printf("*TITLE          = %s \n", title);
		}
		else  {
		  strcpy(title, library[itemid].title);
		  printf("TITLE           = %s \n", title);
	    }
		
		if (strcmp(author, "") != 0) {
		  printf("*AUTHOR         = %s \n",  author);
		}
		else  {
		  strcpy(author, library[itemid].author);
		  printf("AUTHOR          = %s \n", author);
	    }
		
		if (strcmp(subject, "") != 0) {
		  printf("*SUBJECT        = %s \n",  subject);
	    }
		else  {
		  strcpy(subject, library[itemid].subject);
		  printf("SUBJECT          = %s \n", subject);
	    }
		
		if (strcmp(isbn, "") != 0) {
		  printf("*ISBN           = %s \n", isbn);
	    }
		else  {
		  strcpy(isbn, library[itemid].isbn);
		  printf("ISBN            = %s \n", isbn);
	    }
		
		if (strcmp(format, "") != 0) {
		  printf("*FORMAT         = %s \n", format);
	    }
		else  {
		  strcpy(format, library[itemid].format);
		  printf("FORMAT          = %s \n", format);
	    }
		
		if (strcmp(strlocation, "") != 0) {
		  location = atoi(strlocation);  // convert string to integer
		  printf("*SHELF LOCATION = %d \n", location);
	    }
		else {
		  location = library[itemid].location;
		  printf("SHELF LOCATION  = %d \n", location);
	    }
		
		if (strcmp(strqty, "") != 0) {
		  qty = atoi(strqty);           // convert string to integer
		  printf("*QUANTITY       = %d \n", qty);
	    }
		else  {
		  qty = library[itemid].qty;
		  printf("QUANTITY        = %d \n", qty);
	    }
		
        if (strcmp(strprice, "") != 0) {
		  price = atof(strprice);       // convert string to float
		  printf("*PRICE          = $%.2f \n", price);
	    }
		else {
		  price = library[itemid].price;
		  printf("PRICE           = $%.2f \n", price);
	    }
	    
	    yesno = ' ';
	    printf("\nIs this correct? (y/n): ");
	    fflush(stdin);
	    scanf("%c", &yesno);
        if (yesno == 'Y' || yesno == 'y') {
		  tryagain = 0;
		  if (checkItemEdits(itemid, title, author, format, isbn, location, qty, price) ==  0) {
		     strcpy(library[itemid].title, title);
		     strcpy(library[itemid].author, author);
		     strcpy(library[itemid].subject, subject);
		     strcpy(library[itemid].isbn, isbn);
		     strcpy(library[itemid].format, format); 
		     library[itemid].location = location;
		     library[itemid].qty      = qty;
		     library[itemid].price    = price;
	      }
		}
	    else {
		  yesno = ' ';
		  tryagain = 0;
		  printf("Do you want to try again? (y/n): ");
	      fflush(stdin);
	      scanf("%c", &yesno);
          if (yesno == 'Y' || yesno == 'y') {
		    tryagain = 1;
		  }
	   }
	}
  }
}


/***************************************************************************************/ 
/*          Function to return all loaned items from user to library                   */
/***************************************************************************************/ 

static void returnAllItemsfromUser(int userID) {	

    int i, j, k, uID, iID, qty;  
	
	for (i=1; (i <= NumUsers); i++) {
	   if (user[i].id == userID) {
		   uID = i;
		   break;
	   }
	}
	  
	for (i=1; (i <= user[uID].nbloaned); i++) {
	  for (j=1; (j <= NumItems); j++) { 
		  if (library[j].itemid == user[uID].booksloaned[j])  {
	         qty = library[j].qty;
		     qty = qty + 1;
			 library[j].qty = qty;
			 break;
		  }
	  }
    }
	
	user[uID].nbloaned = 0;
}


/***************************************************************************************/ 
/*          Function to reject a request to borrow item from library                  */
/***************************************************************************************/ 

static void rejectBorrowItemRequest(int reqid) {	
    int i, j, nreq, userid;
	
	userid = 0;
	for (i = 1; (i <= NumRequests); i++) {
	   if (requestlist[i].id == reqid) {
		 userid = requestlist[i].userid;
		 break;
	   }
	}
	
	nreq = 0;
	for (i=1; (i <= NumUsers); i++) {
	   if (user[i].id == userid) {
		   
	     for (j=1; (j <= user[i].nbrequested); j++) {
	        if (user[i].reqid[j] != reqid) {
		      nreq = nreq + 1;
			  user[i].booksrequested[nreq] = user[i].booksrequested[j];
			  user[i].reqid[nreq] = user[i].reqid[j];
			}
		 }
		user[i].nbrequested = nreq;
	    break;
	  }
	}
	
	nreq = 0;
	for (i = 1; (i <= NumRequests); i++) {
	  if (requestlist[i].id != reqid) {
		 nreq = nreq + 1;
		 requestlist[nreq] = requestlist[i];
	  }
	   }
	NumRequests = nreq;
	
	printf("Borrow request has been rejected.");
}


/***************************************************************************************/ 
/*          Function to accept a request to borrow item from library                   */
/***************************************************************************************/ 

static void acceptBorrowItemRequest(int reqid) {	
    int i, nreq, qty, uID, lID, userid, itemid;
	
    userid = 0;
	itemid = 0;
	for (i = 1; (i <= NumRequests); i++) {
	   if (requestlist[i].id == reqid) {
		 userid = requestlist[i].userid;
		 itemid = requestlist[i].itemid;
		 break;
	   }
	}
	
    uID = 0;
	for (i=1; (i <= NumUsers); i++) {
	   if (user[i].id == userid) {
		 uID = i;
		 break;
	   }
	}
	
	lID = 0;
	for (i=1; (i <= NumItems); i++) {
	   if (library[i].itemid == itemid) {
		 lID = i;
		 qty = library[i].qty;
		 break;
	   }
	}
	
	
    if (user[uID].nbloaned == MAXBOOKSLOANED) {
	  printf("Error - user has borrowed the maximum number of items.  Press any key to continue...");
	  getchar();
	}
	else if (library[lID].qty = 0) {
	  printf("Error - no items are available to loan.  Press any key to continue...");
	  getchar();
	}
	else {

	  nreq = 0;
	  qty = qty -1;
      library[lID].qty = qty; 
	  user[uID].nbloaned = user[uID].nbloaned + 1;
	  user[uID].booksloaned[user[uID].nbloaned] = itemid;
	  for (i=1; (i <= user[uID].nbrequested); i++) {
	     if (user[uID].reqid[i] != reqid) {
		    nreq = nreq + 1;
			user[uID].reqid[nreq] = user[uID].reqid[i];
			user[uID].booksrequested[nreq] = user[uID].booksrequested[i];
	     }
	  }
	  user[uID].nbrequested = nreq;
	  
	  nreq = 0;
	  for (i = 1; (i <= NumRequests); i++) {
	    if (requestlist[i].id != reqid) {
		  nreq = nreq + 1;
		  requestlist[nreq] = requestlist[i];
		}
	  }
	  NumRequests = nreq;
	  printf("Borrow request has been accepted");
	}
}


/***************************************************************************************/ 
/*                Function to change Admin user name and password                      */
/***************************************************************************************/ 

static int changeAdminUser() {
	int i, error = 0, adminID = 0, match = 0, nattempts = 0, MaxAttempts = 5;
	char tempname[MAXIDLENGTH], temppass[MAXIDLENGTH];
	
	printf("\n");
	printf("\n");
    printf("********************************************\n");
    printf("***  Change Admin Username and Password  ***\n");  
    printf("********************************************\n");
	printf("\n");
	
	// Lookup current admin username and password
	
	for(i = 1; (i <= NumUsers); i++) {
	  if (strcmp(user[i].type, ADMIN) == 0) {
		adminID = i;
		break;
	  }
    }   
	
	if (adminID == 0) {
	  error = 1;
	  printf("Error - admin user account not found\n");
	}
		
	// For security, require user to enter current admin username and password
	
	if (error == 0) {
		error = 1;
		nattempts = 0;
		while (match == 0 && nattempts < MaxAttempts) {
		  nattempts = nattempts + 1;
		  printf("\nEnter current admin username:");
	      scanf("%s", &tempname);
	      printf("Enter current admin password:");
	      scanf("%s", &temppass);
		  if (strcmp(user[adminID].name, tempname) == 0 && strcmp(user[adminID].password, temppass) == 0) {
		    match = 1;
			error = 0;
		  }
		  else if (nattempts == MaxAttempts) {
		   printf("Error - maximum number of failed attempts.\n");
		  }
		  else {
		   printf("Error - incorrect current admin username and password entered\n");
		  }
		}
	}

    // Get new admin username and password, must be at least 8 characers in length
	
	if (error == 0) {
		error = 1;
		nattempts = 0;
		strcpy(tempname, "");
		strcpy(temppass, "");
		
		while (error == 1 && nattempts < MaxAttempts) {
		  nattempts = nattempts + 1;
		  printf("\nEnter new admin username:");
	      scanf("%s", &tempname);
	      printf("Enter new admin password:");
	      scanf("%s", &temppass);
		  if (strcmp(user[adminID].name, tempname) == 0 && strcmp(user[adminID].password, temppass) == 0) {
			printf("Error - new user name and password must be different than current username and password\n");
		  }
		  else if (/*strlen(tempname) < MINIDLENGTH ||*/ strlen(temppass) < MINIDLENGTH) {
			printf("Error - password must be at least 8 characters in length\n");
		  }
		  else {
		     error = 0;
			 strcpy(user[adminID].name, tempname);
			 strcpy(user[adminID].password, temppass);
			 printf("\nAdmin user name and password successfully changed.");\
		  }
		}
	    
		if (error == 1) {
		   printf("Error - maximum number of failed attempts. Press any key to continue.");
		}
	}
	
	return(error);	   
}


/***************************************************************************************/ 
/*                Function to add Guest user account                                   */
/***************************************************************************************/ 

static int addGuestUser() {
	int i, loc, error, guestID, nattempts, MaxAttempts = 5;
	char tempname[MAXIDLENGTH], temppass[MAXIDLENGTH];
	
    printf("\n");
	printf("\n");
    printf("********************************************\n");
    printf("***        Add Guest account             ***\n");  
    printf("********************************************\n");
	printf("\n");
	
	error = 1;
	nattempts = 0;
	strcpy(tempname, "");
	strcpy(temppass, "");
		
	while (error == 1 && nattempts < MaxAttempts) {
	  nattempts = nattempts + 1;
	  printf("\nEnter new Guest username: ");
	  scanf("%s", &tempname);
	  printf("Enter new Guest password: ");
	  scanf("%s", &temppass);
	  
	  if (strlen(temppass) < MINIDLENGTH) {
	     printf("Error - password must be at least 8 characters in length\n");
	  }
	  else {
		error = 0;
	    for(i = 1; (i <= NumUsers); i++) {
	      if (strcmp(user[i].name, tempname) == 0 && strcmp(user[i].type, GUEST) == 0) {
			error = 1;
		    printf("Error - Guest user name already exists\n");
		    break;
		  }
		}
	  }
	}

	if (error == 0) {
	  NumUsers = NumUsers + 1;
	  strcpy(user[NumUsers].name, tempname);
	  strcpy(user[NumUsers].password, temppass);
	  strcpy(user[NumUsers].type, GUEST);
	  LastUserID = LastUserID + 1;
	  user[NumUsers].id = LastUserID;
      user[NumUsers].nbloaned = 0;
      user[NumUsers].nbrequested = 0;
	  printf("\nGuest account successfully created.");
	}
	else {
	  printf("Error - maximum number of failed attempts. Press any key to continue.");
	}
	
	return(error);
}


/***************************************************************************************/ 
/*                Function to delete Guest user account                                */
/***************************************************************************************/ 

static int deleteGuestUser() {
	int i, j, nreq, nuser, error, deleteID;
	char tempname[MAXIDLENGTH];
	
	
	printf("\n");
    printf("********************************************\n");
    printf("***        Delete Guest account          ***\n");  
    printf("********************************************\n");
	
	printf("\nEnter Guest user name:");
	scanf("%s", &tempname);
	
	// Lookup current Guest user name
	
	error = 0;
	deleteID = 0;
	for(i = 1; (i <= NumUsers); i++) {
	  if (strcmp(user[i].name, tempname) == 0 && strcmp(user[i].type, GUEST) == 0) {
		deleteID = user[i].id;
		break;
	  }
    }   
	
	if (deleteID == 0) {
	  error = 1;
	  printf("Error - Guest user account not found.");
	}
	
	// Remove any borrow requests for this Guest user
	
	   
	if (error == 0) {
	  nreq = 0;
	  for(i = 1; (i <= NumRequests); i++) {
		if (requestlist[i].userid != deleteID) {
          nreq = nreq + 1;
		  requestlist[nreq] = requestlist[i]; 
		} 
      }
	  NumRequests = nreq;
	}
	
	   
	// Remove Guest account information
	
	if (error == 0) {
	  nuser = 0;
	  for(i = 1; (i <= NumUsers); i++) {
		if (user[i].id == deleteID) {
		  returnAllItemsfromUser(user[i].id);  // Return any loaned items to library 
		}
		else {
	      nuser = nuser + 1;
		  user[nuser] = user[i];
		}
	  }
	  NumUsers = nuser;  
	  printf("Guest user account successfully deleted.");
	}
	   
	return(error);
}		  		  


/***************************************************************************************/ 
/*                Function to list Borrowing requests                                  */
/***************************************************************************************/ 

void listRequests() {
	int i, j, rID, uID, lID;
	
	printf("\n");
    printf("********************************************\n");
    printf("***     List of Borrowing Requests       ***\n");  
    printf("********************************************\n");
	printf("\n");
	printf("REQ ID    REQUESTER            TITLE                AUTHOR               ISBN        FORMAT           LOC     QTY     PRICE\n");
	
	for(i = 1; (i <= NumRequests); i++) {
	  rID = requestlist[i].id;
	  
	  uID = 0;
	  for (j=1; (j <= NumUsers); j++) {
	    if (requestlist[i].userid == user[j].id) {
	      uID = j;
		  break;
		}
	  }
	   
	  lID = 0;
	  for (j=1; (j <= NumItems); j++) {
	    if (requestlist[i].itemid == library[j].itemid) {
	      lID = j;
		  break;
		}
	  }
	  
      printf("\n%-5i     %-20.20s %-20.20s %-20.20s %-10.10s  %-15.15s  %-5i   %-5i   $%9.2f", rID, user[uID].name, library[lID].title, library[lID].author, library[lID].isbn, library[lID].format, library[lID].location, library[lID].qty, library[lID].price);
	}
}


/***************************************************************************************/ 
/*                Function to Accept or Reject Borrowing Requests                     */
/***************************************************************************************/ 

static void processRequests() {
	int i, rid, error, raction;
	
	printf("\n");
	printf("\n");
    printf("********************************************\n");
    printf("***  Accept/Reject a borrowing request   ***\n");  
    printf("********************************************\n");
	printf("\n"); 
    
	printf("\nEnter Request ID Number:");
	scanf("%d", &rid);
	
	error = 1;
	for (i=1; (i <= NumRequests); i++) {
		if (requestlist[i].id == rid) {
		  error = 0;
		  break;
	    }
	}
	
	if (error == 1) {
		printf("Error - invalid Request ID entered");
	}	
	else {
		printf("\nEnter 0 to Reject, 1 to Accept:");
	    scanf("%d", &raction);
	    if (raction != 0 && raction != 1 ) {
		  printf("Error - invalid option entered");
		}
		else if (raction == 0) {              // Reject borrow request
	      rejectBorrowItemRequest(rid);
	    }
	    else if (raction == 1) {              // Acccept borrow request   
		  acceptBorrowItemRequest(rid);
	    }
	}
}

		
/***************************************************************************************/ 
/*                Function to list contents of library                                 */
/***************************************************************************************/ 

void listLibrary() {
	int i;	
	
	printf("\n");
	printf("\n");
    printf("********************************************\n");
    printf("***     List of Library Items            ***\n");  
    printf("********************************************\n");
	printf("\n");
	
	printf(" ID       TITLE                AUTHOR               SUBJECT              ISBN        FORMAT           LOC     QTY     PRICE\n");
    for(i = 1; (i <= NumItems); i++) {
	  printf("\n%-5i     %-20.20s %-20.20s %-20.20s %-10.10s  %-15.15s  %-5i   %-5i   $%9.2f", library[i].itemid, library[i].title, library[i].author, library[i].subject, library[i].isbn, library[i].format, library[i].location, library[i].qty, library[i].price);
	}
}


/***************************************************************************************/ 
/*                Function to list user account information                            */
/***************************************************************************************/ 

static void listUsers() {
	int i;

	printf("\n");
	printf("\n");
    printf("********************************************\n");
    printf("***     List of User Accounts            ***\n");  
    printf("********************************************\n");
	printf("\n");
	
	printf("ID        USER NAME            PASSWORD             ACCOUNT        LOANED ITEMS    LOAN REQUESTS\n");
    for (i = 1; (i <= NumUsers); i++) {
       printf("\n%-5i     %-20.20s %-20.20s %-10.10s           %-10i    %-10i", user[i].id, user[i].name, user[i].password, user[i].type, user[i].nbloaned, user[i].nbrequested);
	}
}


/***************************************************************************************/ 
/*           Function to request to borrow an item from the library                    */
/***************************************************************************************/  

static void requestToBorrowLibraryItem() {
    int i, j, itemid, match, days;
	char stritemid[MAXITEMLENGTH], time[MAXIDLENGTH];
  
    printf("\n");
    printf("\n");
    printf("********************************************\n");
    printf("***  Request to Borrow a Library Item    ***\n");  
    printf("********************************************\n"); 
    printf("\n"); 
    
	// Get Item ID
	
    printf("\nEnter ITEM ID Number:");
	fflush(stdin);
	fgets(stritemid, MAXITEMLENGTH, stdin);
	stritemid[strlen(stritemid) - 1] = '\0';  // remove the line break character
	itemid = atoi(stritemid);                 // convert string to integer

	// Get number of days

	printf("\nFor how many DAYS?: ");
	fflush(stdin);
	fgets(time, MAXIDLENGTH, stdin);
	time[strlen(time) - 1] = '\0';  // remove the line break character
	days = atoi(time);                 // convert string to integer

	
	// Make sure ITEM ID is valid
	
	match = 0;
	for (i=1; (i <= NumItems); i++) {
		if (library[i].itemid == itemid) {
		  match = 1;
		  break;
	    }
	}
    if (match == 0) {
	  printf("Error - ITEM ID is invalid\n");
	}
	// Make sure guest user has not reached the request limit
	else {
		for (i=1; (i <= NumUsers); i++) {
			if (user[i].id == CurrentUserID) {
				if (user[i].nbrequested >= MAXREQUESTS) {
					printf("Error - User has reached the maximum number of loan requests\n");
				}
				// assign borrow request
				else {
					user[i].nbrequested = user[i].nbrequested + 1;
					user[i].booksrequested[user[i].nbrequested] = itemid;
					NumRequests = NumRequests + 1;
					LastRequestID = LastRequestID + 1;
					user[i].reqid[user[i].nbrequested] = LastRequestID;
					requestlist[NumRequests].id = LastRequestID;
					requestlist[NumRequests].userid = CurrentUserID;
					requestlist[NumRequests].itemid = itemid;
					for (j = 1; (j <= NumRequests); j++) {
						//requestlist[user[i].reqid[j]].time = days;
					}
					printf("Borrow request for %d days successfully submitted. Total Requests = %d Last Request ID = %d", days, NumRequests, LastRequestID);
				}
				break;
			}
		}
	}
}


/***************************************************************************************/ 
/*           Function to search for an item in the library                             */
/***************************************************************************************/  

static void searchForLibraryItem() {
	int i, error, option, itemid, match;
	char stroption[MAXITEMLENGTH], stritemid[MAXITEMLENGTH], title[MAXITEMLENGTH], author[MAXITEMLENGTH], format[MAXITEMLENGTH], isbn[MAXITEMLENGTH], subject[MAXITEMLENGTH];
	
	error = 0;

    printf("*****************************************************************************\n");
    printf("*                                                                           *\n");
    printf("*                        Search for Library Items                           *\n");
    printf("*                                                                           *\n");
    printf("*                               Options                                     *\n");
    printf("*                                                                           *\n");
    printf("*           1 - Search by ITEM ID       4 - Search by SUBJECT               *\n");
    printf("*           2 - Search by TITLE         5 - Search by FORMAT                *\n");
    printf("*           3 - Search by AUTHOR        6 - Search by ISBN                  *\n");
    printf("*                                                                           *\n");
    printf("*           0 - Exit                                                        *\n");
	printf("*                                                                           *\n");
    printf("*****************************************************************************\n");
	
	// Get search option
	
	printf("\nEnter Search Option (0-6): ");
	fflush(stdin);
	fgets(stroption, MAXITEMLENGTH, stdin);
	stroption[strlen(stroption) - 1] = '\0'; // remove the line break character
	option = atoi(stroption);                // convert string to integer
	
	if (option < 0 || option > 6) {
	   printf("Error - invalid Search Option entered\n");
	}
	else {
	    
	// Lookup and display items in library using search criteria
	
      switch (option) {
		  
	    case 0:
	    error = 1;
        break;
		
        case 1: // search by ITEM ID
	    printf("\nEnter ITEM ID: ");
	    fflush(stdin);
        fgets(stritemid, MAXITEMLENGTH, stdin);
	    stritemid[strlen(stritemid) - 1] = '\0';    // remove the line break character
	    itemid = atoi(stritemid);                   // convert string to integer
        match = 0;
        for (i=1; (i <= NumItems); i++) {
          if (library[i].itemid == itemid) {
		    match = 1;
			printf("ID        TITLE                AUTHOR               SUBJECT              ISBN        FORMAT           LOC     QTY     PRICE\n");
		    printf("\n%-5i     %-20.20s %-20.20s %-20.20s %-10.10s  %-15.15s  %-5i   %-5i   $%9.2f", library[i].itemid, library[i].title, library[i].author, library[i].subject, library[i].isbn, library[i].format, library[i].location, library[i].qty, library[i].price);
			break;
		  }
		}
	    if (match == 0) {
		  printf("\n Error - no library item matching the search criteria was found\n");
	    }
        break;
	
	    case 2:  // search by TITLE
        printf("\nEnter TITLE: ");
	    fflush(stdin);
        fgets(title, MAXITEMLENGTH, stdin);
	    title[strlen(title) - 1] = '\0';            // remove the line break character
        match = 0;
        for (i=1; (i <= NumItems); i++) {
          if (strcmp(library[i].title, title) == 0) {
		    match = match + 1;
			if (match == 1){
			  printf("ID        TITLE                AUTHOR               SUBJECT              ISBN        FORMAT           LOC     QTY     PRICE\n");
			}
		    printf("\n%-5i     %-20.20s %-20.20s %-20.20s %-10.10s  %-15.15s  %-5i   %-5i   $%9.2f", library[i].itemid, library[i].title, library[i].author, library[i].subject, library[i].isbn, library[i].format, library[i].location, library[i].qty, library[i].price);
		  }
		}
	    if (match == 0) {
		  printf("\n Error - no library item matching the search criteria was found\n");
	    }
        break;
		
		case 3:  // search by AUTHOR
        printf("\nEnter AUTHOR: ");
	    fflush(stdin);
        fgets(author, MAXITEMLENGTH, stdin);
	    author[strlen(author) - 1] = '\0';            // remove the line break character
        match = 0;
        for (i=1; (i <= NumItems); i++) {
          if (strcmp(library[i].author, author) == 0) {
		    match = match + 1;
			if (match == 1){
			  printf("ID        TITLE                AUTHOR               SUBJECT              ISBN        FORMAT           LOC     QTY     PRICE\n");
			}
		    printf("\n%-5i     %-20.20s %-20.20s %-20.20s %-10.10s  %-15.15s  %-5i   %-5i   $%9.2f", library[i].itemid, library[i].title, library[i].author, library[i].subject, library[i].isbn, library[i].format, library[i].location, library[i].qty, library[i].price);
		  }
		}
	    if (match == 0) {
		  printf("\n Error - no library item matching the search criteria was found\n");
	    }
        break;
		
		case 4:  // search by SUBJECT
        printf("\nEnter SUBJECT: ");
	    fflush(stdin);
        fgets(subject, MAXITEMLENGTH, stdin);
	    subject[strlen(subject) - 1] = '\0';            // remove the line break character
        match = 0;
        for (i=1; (i <= NumItems); i++) {
          if (strcmp(library[i].subject, subject) == 0) {
		    match = match + 1;
			if (match == 1){
			  printf("ID        TITLE                AUTHOR               SUBJECT              ISBN        FORMAT           LOC     QTY     PRICE\n");
			}
		    printf("\n%-5i     %-20.20s %-20.20s %-20.20s %-10.10s  %-15.15s  %-5i   %-5i   $%9.2f", library[i].itemid, library[i].title, library[i].author, library[i].subject, library[i].isbn, library[i].format, library[i].location, library[i].qty, library[i].price);
		  }
		}
	    if (match == 0) {
		  printf("\n Error - no library item matching the search criteria was found\n");
	    }
        break;
		
		case 5:  // search by FORMAT
        printf("\nEnter FORMAT: ");
	    fflush(stdin);
        fgets(format, MAXITEMLENGTH, stdin);
	    format[strlen(format) - 1] = '\0';            // remove the line break character
        match = 0;
        for (i=1; (i <= NumItems); i++) {
          if (strcmp(library[i].format, format) == 0) {
		    match = match + 1;
			if (match == 1){
			  printf("ID        TITLE                AUTHOR               SUBJECT              ISBN        FORMAT           LOC     QTY     PRICE\n");
			}
		    printf("\n%-5i     %-20.20s %-20.20s %-20.20s %-10.10s  %-15.15s  %-5i   %-5i   $%9.2f", library[i].itemid, library[i].title, library[i].author, library[i].subject, library[i].isbn, library[i].format, library[i].location, library[i].qty, library[i].price);
		  }
		}
	    if (match == 0) {
		  printf("\n Error - no library item matching the search criteria was found\n");
	    }
        break;
		
		case 6:  // search by ISBN
        printf("\nEnter ISBN: ");
	    fflush(stdin);
        fgets(isbn, MAXITEMLENGTH, stdin);
	    isbn[strlen(isbn) - 1] = '\0';            // remove the line break character
        match = 0;
		printf("ID        TITLE                AUTHOR               SUBJECT              ISBN        FORMAT           LOC     QTY     PRICE\n");
        for (i=1; (i <= NumItems); i++) {
          if (strcmp(library[i].isbn, isbn) == 0) {
		    match = 1;
		    printf("\n%-5i     %-20.20s %-20.20s %-20.20s %-10.10s  %-15.15s  %-5i   %-5i   $%9.2f", library[i].itemid, library[i].title, library[i].author, library[i].subject, library[i].isbn, library[i].format, library[i].location, library[i].qty, library[i].price);
			break;
		  }
		}
	    if (match == 0) {
		  printf("\n Error - no library item matching the search criteria was found\n");
	    }
        break;
      }
    }
}


/***************************************************************************************/ 
/*           Function to display Guest menu and process selected option                */
/***************************************************************************************/  

static void displayGuestMenu() {

  int option, exit, error;
  
  exit = 0;
  while (exit == 0) {	
    printf("\n");
    printf("\n");
	printf("\n");
    printf("****************************************************************************************\n");
    printf("*                                                                                      *\n");
    printf("*                     Welcome to the MEDKS Library Management System                   *\n");
    printf("*                                                                                      *\n");
    printf("*                               Guest User Menu Options                                *\n");
    printf("*                                                                                      *\n");
    printf("*                             1 - Search for item                                      *\n");
    printf("*                             2 - Request to borrow item                               *\n");
	printf("*                             3 - List library items                                   *\n");
	printf("*                             4 - View list of borrowing requests                      *\n");
    printf("*                             0 - Exit                                                 *\n");
    printf("*                                                                                      *\n");
    printf("****************************************************************************************\n");
    printf("\n");
  
    error = 1;
	while (error == 1){
      printf("\nEnter Option (0-4):");
      scanf("%d", &option);
	  if (option >= 0 && option <= 4) {
	    error = 0;
	  }
	  else
	  {
	    printf("Error - invalid entry\n");
	    fflush(stdin);
	  }
	}

    switch (option){
		  
	  case 0:
	  printf("\nThank you for using MEDKS Library Management Systems!");
	  printf("\nPress any key to exit...");
      fflush(stdin);
      getchar();
	  exit = 1;
      break;
		
      case 1:
	  searchForLibraryItem();
      break;
	
	  case 2:
	  requestToBorrowLibraryItem();
      break;

	  case 3:
	  listLibrary();
	  break;

	  case 4:
	  listRequests();
	  break;

    }
  
    if (option !=0 ) {
	  printf("\n\nPress any key to continue...");
      fflush(stdin);
      getchar();
    }
  }
}


/***************************************************************************************/ 
/*           Function to display Admin user menu and process selected option           */
/***************************************************************************************/ 

static void displayAdminMenu() {
	
  int option, exit, error;
  
  exit = 0;
  while (exit == 0) {
    printf("\n");
    printf("\n");
    printf("\n");
    printf("****************************************************************************************\n");
    printf("*                                                                                      *\n");
    printf("*                   Welcome to the MEDKS Library Management System                     *\n");
    printf("*                                                                                      *\n");
    printf("*                              Admin User Menu Options                                 *\n");
    printf("*                                                                                      *\n");
    printf("*      1 - Change admin username and password      6  - Add item to library            *\n");
    printf("*      2 - Add a guest user account                7  - Edit item in library           *\n");
    printf("*      3 - Remove a guest user account             8  - Delete item from library       *\n");
    printf("*      4 - View list of borrowing requests         9  - List library items             *\n");
    printf("*      5 - Accept/Reject a borrowing request       10 - List user accounts             *\n");
    printf("*                                                                                      *\n");
	printf("*      0 - Exit                                                                        *\n");
	printf("*                                                                                      *\n");
    printf("****************************************************************************************\n");
	printf("\n");

    error = 1;
	while (error == 1){
      printf("\nEnter Option (0-10):");
      scanf("%d", &option);
	  if (option >= 0 && option <= 10) {
	    error = 0;
	  }
	  else
	  {
	    printf("Error - invalid entry\n");
	    fflush(stdin);
	  }
	}

    switch (option){
		  
	  case 0:
	  printf("\nThank you for using MEDKS Library Management Systems!");
	  printf("\nPress any key to exit...");
      fflush(stdin);
      getchar();
	  exit = 1;
      break;
		
      case 1:
	  changeAdminUser();
      break;
	
	  case 2:
      addGuestUser();
      break;
	
	  case 3:
      deleteGuestUser();
      break;
	
	  case 4:
      listRequests();
      break;
	
	  case 5:
      processRequests();
      break;
	
	  case 6:
	  addItemtoLibrary();
      break; 
	
	  case 7:
	  editLibraryItem();
      break;
	
	  case 8:
	  deleteItemfromLibrary();
      break;
	
	  case 9:
	  listLibrary();
	  getchar();
      break;

	  case 10:
	  listUsers();
      break;
    }
  
    if (option !=0 ) {
	  printf("\n\nPress any key to continue...");
      fflush(stdin);
      getchar();
    }
  }
}


/***************************************************************************************/ 
/*           Function to control user login to the LMS                                 */
/***************************************************************************************/ 

static int userLogin() {
  int i, nattempts, usertype, MaxAttempts;
  char tempname[MAXIDLENGTH], temppass[MAXIDLENGTH];

  usertype = 0;  
  nattempts = 0;
  MaxAttempts = 5;
  CurrentUserID = 0;
  CurrentUserType = 0;

  printf("\n");
  printf("\n");
  printf("\n");
  printf("****************************************************************************************************\n");
  printf("*                                                                                                  *\n");
  printf("*                          Welcome to the MEDKS Library Management System                          *\n");
  printf("*                                                                                                  *\n");
  printf("*                                                                                                  *\n");
  printf("****************************************************************************************************\n");
  printf("\n");
	
  while (usertype == 0 && nattempts < MaxAttempts) {
    nattempts = nattempts + 1;
    printf("\nEnter username: ");
	scanf("%s", &tempname);
	printf("Enter password: ");
	scanf("%s", &temppass);
    for(i = 1; (i <= NumUsers); i++) {
	  if (strcmp(user[i].name, tempname) == 0 && strcmp(user[i].password, temppass) == 0 && strcmp(user[i].type, GUEST) == 0) {
		CurrentUserID = user[i].id;
		CurrentUserType = 1;
	    usertype = 1;
		break;
	  }
	 else if (strcmp(user[i].name, tempname) == 0 && strcmp(user[i].password, temppass) == 0 && strcmp(user[i].type, ADMIN) == 0) {
		CurrentUserID = user[i].id;
		CurrentUserType = 2;
		usertype = 2;
		break;
	 }
    }
    
	if (usertype == 0 && nattempts == MaxAttempts) {
	  printf("Error - maximum number of failed login attempts.\n");
    }
    else if (usertype == 0) {
	  printf("Error - invalid username and password\n");
	}
  }
  return(usertype);  //0=login error, 1=guest user, 2=admin user
}


/***************************************************************************************/ 
/*       Function to initialize LMS user and library records from external files       */
/***************************************************************************************/ 

void initializeLMSfromFile() {

  readUserFile();
  readLibraryFile();
  
}


/***************************************************************************************/ 
/*        Function to write LMS user and library records to external files             */
/***************************************************************************************/ 

void saveLMStoFile() {
	
  writeUserFile();
  writeLibraryFile();
  
}


/***************************************************************************************/ 
/*                            Function to start LMS                                    */
/***************************************************************************************/ 

static void startLMS() {
  int AccessType;
  
   AccessType = userLogin();
   if (AccessType == 1) {
     displayGuestMenu();
   }
   else if (AccessType == 2) {
     displayAdminMenu();
   }
}


/***************************************************************************************/ 
/*                                Main Program                                         */
/***************************************************************************************/ 
void main() {

  initializeLMSfromFile();

  startLMS();
   
  saveLMStoFile();
}