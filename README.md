# _TRate_trl_
The _TRate_trl_ program computes "rate" of each transcript according to given coverage file. Transcripts are coded by coordinates of their exons (bed file for now, gtf/gff in future). Rate is computed as total _mass_ of exons within the transcript divided by D = 2*read_length*transcript_length/1000. _Mass_ is taken as approximation of the area under coverage curve, i.e. sum of areas of coverage rectangles. The _transcript_length_ is diefined as sum of exon's lengths.

The _TRate_trl_ program takes in three arguments in fixed order.

1. Exons_file - coordinate sorted bed file that provides locations of exons for the corresponding transcript provided in column 4.

Exons_file format example

	C0000570	10420	10640	Transcript1
	C0000570	128078	128300	Transcript2
	C0000570	128350	128410	Transcript2
	C0000571	12845	13133	Transcript3
	C0000571	13211	13274	Transcript3
	C0000571	33100	33200	Transcript4
	C0000571	33440	33500	Transcript4

2. Coverage_file - coordinate sorted file in bedgraph format - it can contain coverage data (usually normalized) from RNAseq study, ChIPseq, ATACseq and so on.

Coverage_file format example

	C0000570	128417	128420	1.021174
	C0000570	128420	128452	1.010587
	C0000571	33336	33436	5.021174
	C0000571	33437	33450	5.1234
 
3. Read length (for single end libraries) and doubled read length for paired end libraries (e.g. 300 for paired end reads of length 150)

## _USAGE_
### Prerequisites (MUST be in your PATH)
	BEDTOOLS
	AWK
    g++
	
### Installation
Download TRate_trl

cd TRate_trl

make		

In file TRate_trl.sh edit path to TRate_trl folder, e.g.

FOLDER_PATH="your/path/TRate_trl"

### Run TRate_trl on test data

     ./TRate_trl.sh ./data/Exons_file.sbed ./data/Coverage_file.bg 300

Output will be in a file Coverage_file.rate_trl 

Output format

	Transcript1	0.769264
	Transcript2	2.29329
	Transcript3	0
	Transcript4	1.60106

Transcript rate = 0 if no coverage data were found for this transcript.

 
