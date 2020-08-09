/* 
 * This is custom library for converting variables to Packed BCD Digits and strings!
 * 
 */

/* 
 * File: bcd_string.h  
 * Author: Stoian Banchev
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef BCD_STRING_H
#define	BCD_STRING_H



// Swap nibbles function input: 0x12 -> Output: 0x21
//=================================================================================
char SwapByteNibbles(char x) 
{ 
    return ( (x & 0x0F) << 4 | (x & 0xF0) >> 4 ); 
} 



//Some custom write by Me "rotate add 3" algorithm for convert Byte to Packed BCD Digit.
//=================================================================================
 int ByteToBCD (unsigned char Byte){
 
     unsigned int BCD_Result = 0;
     unsigned char index = 0;
     
            for (index = 0;index < 7;index++){
                          
                if(Byte & (0x80 >> index)){
                    BCD_Result |=  0x0001; //set LSB of BCD_Result as 1
                }
                else{
                    BCD_Result &= 0xfffe; //set LSB of BCD_Result as 0
                }

                //Start Check Nibbles and add 3 if nibble is greather then 5
                
                    //Check first nibble
                    if ((BCD_Result & 0x000f) > 0x0004){

                        BCD_Result += 0x0003;//add 3 to first nibble

                    }

                    //Check second nibble
                    if ((BCD_Result & 0x00f0) > 0x0040){

                        BCD_Result += 0x0030;//add 3 to second nibble

                    }

                    //Check third nibble
                    if ((BCD_Result & 0x0f00) > 0x0400){

                        BCD_Result += 0x0300;//add 3 to third nibble

                    }
            
            
                //Rotate to left one bit BCD_Result
                BCD_Result <<= 1;     
            
                
            }
            
            //Check the last bit of Byte and put it to da LSB of BCD_Result
            if(Byte & (0x80 >> 7)){
                    BCD_Result |=  0x0001; //set LSB of BCD_Result as 1
            }
     
     return BCD_Result;
 }

/*==============================================================================
 ===============================================================================
 HERE START FUNCTION FROM WEB FORUMS JUST FOR TEST
================================================================================  
 ==============================================================================*/
 
 
// First int to BCD 1.333 mS   execution time at 16MHz
//=====================================================
unsigned long toPackedBcd (unsigned int val)
{
  unsigned long bcdresult = 0; char i;


  for (i = 0; val; i++)
  {
    ((char*)&bcdresult)[i / 2] |= i & 1 ? (val % 10) << 4 : (val % 10) & 0xf;
    val /= 10;
  }
  return bcdresult;
}

// Second int to BCD 0.856 mS execution time at 16MHz
//======================================================
unsigned long toPakedBcd2(unsigned int binaryInput)
{
    unsigned long bcdResult = 0;
    int shift = 0;
    
while (binaryInput > 0) {
      bcdResult |= (binaryInput % 10) << (shift++ << 2);
      binaryInput /= 10;
   }

return bcdResult;
}

//convert 16bit integer to 32bit packed BCD
//3rd Attempt :)) 0,843 mS execution time at 16MHz
//===================================================

unsigned long dec2bcd(unsigned int dec) 
{
    uint32_t result = 0;
    int shift = 0;

    while (dec)
    {
        result +=  (dec % 10) << shift;
        dec = dec / 10;
        shift += 4;
    }
    return result;
}




////------------------------------ string reverse function -----------------------------//
// 
// void reverse(char s[])
// {
//   int c, i, j;
// 
//   for (i = 0, j = strlen(s)-1; i < j; i++ , j--)
//   {
//     c = s[i];
//     s[i] = s[j];
//     s[j] = c;
//   }
// }  


////----------------------------- my_itoa_2 function --------------------------------//
// // returns two digits with a leading zero if required
// 
// void my_itoa_2(unsigned int n, char s[])
// {
//   int i;
// 
//   i = 0;
//   do 
//   {
//     s[i++] = n % 10 + '0';
//   }
//   while ((n /= 10) >= 1);
//   if ( i == 1)
//     s[i++] = '0';
//   s[i] = '\0'; 
//   reverse(s);
// }
 
 
 
 

 


#endif	/* XC_HEADER_TEMPLATE_H */
