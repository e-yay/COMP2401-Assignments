#include <stdio.h>
#include <math.h>

int main() {
  float width, length, innerwidth, innerlength ;
  int paver_needed, curb_needed, row, col, colcurbs, rowcurbs;
  float paver_length = 7.75;
  float paver_width = 7.75;
  float curb_width = 4.3;
  float curb_length = 11.8;
  float price_curb;
  float price_paver;
  float total_price;
  float taxed_total_price;

  //Get user input ot determine legth of the patio
  printf("What is your desired patio width (in feet)? \n");
  scanf("%f", &width);
  printf("What is your desired patio length (in feet)? \n");
  scanf("%f", &length);
  //Establish minimum input condition
  if ((length<2) || (width<2)){
      printf("Patio dimensions are not big enough.");
      return 0;
  } else {
      //Convert feet to inches
      width *= 12;
      length *= 12;
      //Calculate width of the inner dimensions of the patio(inner rectangle)
      innerwidth = (width-(2*curb_width));
      innerlength = (length-(2*curb_width));
      //Calculate the number of rows and columns of tiles
      row=ceil((innerwidth/paver_width));
      col=ceil((innerlength/paver_length));
      //Calculate the no of paver tiles  needed
      paver_needed=row*col;
      //Calculate the no of curb tiles needed
      rowcurbs= ceil(2*(length/curb_length));
      colcurbs= ceil(2*(innerwidth/curb_length));
      curb_needed=rowcurbs+colcurbs;
      //Calculate price of paver and curb tiles needed individually
      price_paver= paver_needed*3.90;
      price_curb= curb_needed*2.48;
      total_price = price_paver + price_curb;
      taxed_total_price = (total_price * 0.13) + total_price;
      //Print Results
      printf("You will need %d pavers.\n", paver_needed);
      printf("You will need %d curbs.\n", curb_needed);
      printf("Paver price will be $ %.2f\n", price_paver);
      printf("Curb price will be $ %.2f\n", price_curb);
      printf("Total price with tax will be $ %.2f\n", taxed_total_price);
      }
    return 0;
  }
