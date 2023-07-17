
#include <unistd.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <string.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;
 
int main( int argc , char** argv ) {


   char fName[1000]="", fff[1000]="";
   int L=300; //read length, should be provided as an input, default 150
   
  if (optind >= argc) {
        fprintf(stderr, "Expected area_file(*ra) read_length\n");
        fprintf(stderr, "Usage: area_file(*ra) read_length\n");
        exit(EXIT_FAILURE);
    }  

  if (argc < 2) {
        fprintf(stderr, "Expected area_file(*ra) and read_length\n");
        fprintf(stderr, "Usage: area_file(*ra) read_length\n");
        exit(EXIT_FAILURE);
    }  

   //strncat(fname,"",0);
   strncat(fName,argv[optind],strlen(argv[optind]));
   //printf ("fName=%s argv[2] = %s\n",fName,argv[2]);

   L=atoi(argv[2]);
   printf("L=%d\n",L);
      
   std::ifstream area_file( fName );
   if (!area_file) {
	fprintf(stderr, "Can't open input file %s\n",fName);	
        exit(EXIT_FAILURE);
    }

   std::string line;
   string trans="", trans_pred="", areas, begs, ends;
   int linecount=0, beg, end, beg1, end1, W=0;
   float rate, area, area_sum=0, D;

   sprintf(fff, "%se_trl", fName);
   std::ofstream outfile(fff);
   printf("out=%s",fff);
   beg1=-1; end1=-1;
    while ( getline( area_file , line ) ) {
	 //std::cout << linecount << ": " << line << '\n' ;//supposing '\n' to be line end
	 //linecount++ ;
	 stringstream ss(line);
         getline(ss,trans, '\t');
	 //	cout << "Transcript: " << trans << " trans_pred: "<<trans_pred<<endl;
         getline(ss,areas, '\t');
	 area=atof(areas.c_str());
         //       cout << "area: " << area <<endl;
         getline(ss,begs, '\t');
         beg=atoi(begs.c_str());
         //       cout << "beg: " << beg <<endl;

         getline(ss,ends, '\t');
         end=atoi(ends.c_str());
         //       cout << "end: " << end <<endl;

        if(trans_pred != trans) 
         {
          D=(float)L*W/1000; 
          rate=area_sum/D;
          //printf ("area_sum=%f D=%f W=%d rate=%f\n", area_sum, D, W,rate);              
          if(trans_pred!="") outfile << trans_pred << "\t" << rate << endl;   

           area_sum=area;
           W=end-beg;
           beg1=beg; end1=end;
	 }
        else
            {area_sum+=area;
             if(beg!=beg1 && end!=end1) 
                {W+=(end-beg);
                 beg1=beg; end1=end;
                }  
                
            } 


         trans_pred=trans;
        }

   //process last record
        D=(float)L*W/1000; 
        rate=area_sum/D;
         // printf ("area_sum=%f D=%f W=%d rate=%f\n", area_sum, D, W,rate);              
        outfile << trans_pred << "\t" << rate << endl;   

   outfile.close();
   area_file.close();
  cout << endl << "all transcripts are processed";
}
