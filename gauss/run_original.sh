#!/bin/bash

# Options
#FILES=*.bmp # list of bitmaps to analyse
#FOLDER=Images
#Images/9ms/10ms

FOLDER=Images
BACKGROUNDFOLDER=/Background_removed   # keep slash
FILESTEM="image_cam_3_"
#loop over molasses
for loop_molasses in {0..0}
do
MOLASSES=$loop_molasses\ms
OUTPUT=$loop_molasses\ms.txt
rm $OUTPUT
DATADIR=Data/$MOLASSES
LOGDIR=Log/$MOLASSES
PLOTDIR=Plots/$MOLASSES
if [ ! -d $DATADIR ]; then
  mkdir $DATADIR
fi
if [ ! -d $PLOTDIR ]; then
  mkdir $PLOTDIR
fi
if [ ! -d $LOGDIR ]; then
  mkdir $LOGDIR
fi

TEMPOUT_x=output_x.txt
TEMPOUTZERO_x=output_zero_x.txt
if [ -e $TEMPOUT_x ]; then
    rm $TEMPOUT_x
fi
if [ -e $TEMPOUTZERO_x ]; then
    rm $TEMPOUTZERO_x
fi

TEMPOUT_y=output_y.txt
TEMPOUTZERO_y=output_zero_y.txt
if [ -e $TEMPOUT_y ]; then
    rm $TEMPOUT_y
fi
if [ -e $TEMPOUTZERO_y ]; then
    rm $TEMPOUTZERO_y
fi

#loop over waiting times
for loop_wait in {5..9}
do
WAITTIME=$loop_wait\ms
DATADIR=Data/$MOLASSES/$WAITTIME
LOGDIR=Log/$MOLASSES/$WAITTIME
PLOTDIR=Plots/$MOLASSES/$WAITTIME
if [ ! -d $DATADIR ]; then
  mkdir $DATADIR
fi
if [ ! -d $PLOTDIR ]; then
  mkdir $PLOTDIR
fi
if [ ! -d $LOGDIR ]; then
  mkdir $LOGDIR
fi
TEMP=temp.txt
OUTFILE=results.txt

mkdir $FOLDER/$MOLASSES/$WAITTIME$BACKGROUNDFOLDER
#echo "made dir" 
echo $FOLDER/$MOLASSES/$WAITTIME$BACKGROUNDFOLDER
rm $FOLDER/$MOLASSES/$WAITTIME$OUTFILE
for i in {100..350} # loop through bitmaps
do
  file1=$FOLDER/$MOLASSES/$WAITTIME/$FILESTEM$i.bmp
  file2=$FOLDER/$MOLASSES/$WAITTIME$BACKGROUNDFOLDER/$FILESTEM$i.bmp
  #echo $file1
  #echo $file2	
  #echo Analysing $file
  ./Background_subtract_aoi $file1
  echo -e "$i\t" `./sum_brightness $file2` >> $FOLDER/$MOLASSES/$WAITTIME$OUTFILE
done
echo -e "$loop_wait\t" `python find_flash.py $FOLDER $MOLASSES $WAITTIME$OUTFILE` >> $OUTPUT
FRAME=$(python find_flash.py $FOLDER $MOLASSES $WAITTIME$OUTFILE)
./Background_subtract $FOLDER/$MOLASSES/$WAITTIME/$FILESTEM$FRAME.bmp
ZEROFRAME=$(python find_zero.py $FOLDER $MOLASSES $WAITTIME$OUTFILE)
./Background_subtract $FOLDER/$MOLASSES/$WAITTIME/$FILESTEM$ZEROFRAME.bmp
FILE=$WAITTIME.bmp
cp $FOLDER/$MOLASSES/$WAITTIME$BACKGROUNDFOLDER/$FILESTEM$FRAME.bmp $FILE
ZEROFILE=0_$WAITTIME.bmp
cp $FOLDER/$MOLASSES/$WAITTIME$BACKGROUNDFOLDER/$FILESTEM$ZEROFRAME.bmp $ZEROFILE

#Fit to the release frame - for x
if [ -e "$FILE" ]
then
./bmptotxt $FILE
mv $FILE.txt $DATADIR/$FILE.txt
python rowcol_2.py $DATADIR/$FILE.txt
gnuplot -e  "filename='$DATADIR/$FILE';psname='$PLOTDIR/$FILE-x.ps';title='$DATADIR/$FILE x-axis';datafile='$DATADIR/$FILE-x.txt';" plot_mot_x.gnu
mv fit.log $LOGDIR/$FILE-x.log
echo -e "$FILE\t"$(grep "+/-" $LOGDIR/$FILE-x.log | grep "sigma_x") >> radii_x.txt
resultx=$(grep "+/-" $LOGDIR/$FILE-x.log | grep "sigma_x")
stringarrayx=($resultx)
sig_x=${stringarrayx[2]}
sig_x=${sig_x/-/}
sig_x_err=${stringarrayx[4]}
MS=$(echo $FILE | tr -dc '0-9')
echo -e "$MS\t$sig_x\t$sig_x_err" >> $TEMPOUT_x
fi

#Fit to the release frame - for y
if [ -e "$FILE" ]
then
gnuplot -e  "filename='$DATADIR/$FILE';psname='$PLOTDIR/$FILE-y.ps';title='$DATADIR/$FILE y-axis';datafile='$DATADIR/$FILE-y.txt';" plot_mot_y.gnu
mv fit.log $LOGDIR/$FILE-y.log
echo -e "$FILE\t"$(grep "+/-" $LOGDIR/$FILE-y.log | grep "sigma_y") >> radii_y.txt
resulty=$(grep "+/-" $LOGDIR/$FILE-y.log | grep "sigma_y")
stringarrayy=($resulty)
sig_y=${stringarrayy[2]}
sig_y=${sig_y/-/}
sig_y_err=${stringarrayy[4]}
MS=$(echo $FILE | tr -dc '0-9')
echo -e "$MS\t$sig_y\t$sig_y_err" >> $TEMPOUT_y
fi

#Fit to the zeroth frame for x
if [ -e "$ZEROFILE" ]
then
./bmptotxt $ZEROFILE
mv $ZEROFILE.txt $DATADIR/$ZEROFILE.txt
python rowcol_2.py $DATADIR/$ZEROFILE.txt
gnuplot -e  "filename='$DATADIR/$ZEROFILE';psname='$PLOTDIR/$ZEROFILE-x.ps';title='$DATADIR/$ZEROFILE x-axis';datafile='$DATADIR/$ZEROFILE-x.txt';" plot_mot_zero_x.gnu
mv fit.log $LOGDIR/$ZEROFILE-x.log
echo -e "$FILE\t"$(grep "+/-" $LOGDIR/$ZEROFILE-x.log | grep "sigma_zero_x") >> radii_zero_x.txt
result_zero_x=$(grep "+/-" $LOGDIR/$ZEROFILE-x.log | grep "sigma_zero_x")
stringarray_zero_x=($result_zero_x)
sig_zero_x=${stringarray_zero_x[2]}
sig_zero_x=${sig_zero_x/-/}
sig_zero_x_err=${stringarray_zero_x[4]}
MS=$(echo $ZEROFILE | tr -dc '0-9')
echo -e "$sig_zero_x" >> $TEMPOUTZERO_x
fi

#Fit to the zeroth frame for y
if [ -e "$ZEROFILE" ]
then
gnuplot -e  "filename='$DATADIR/$ZEROFILE';psname='$PLOTDIR/$ZEROFILE-y.ps';title='$DATADIR/$ZEROFILE y-axis';datafile='$DATADIR/$ZEROFILE-y.txt';" plot_mot_zero_y.gnu
mv fit.log $LOGDIR/$ZEROFILE-y.log
echo -e "$FILE\t"$(grep "+/-" $LOGDIR/$ZEROFILE-y.log | grep "sigma_zero_y") >> radii_zero_y.txt
result_zero_y=$(grep "+/-" $LOGDIR/$ZEROFILE-y.log | grep "sigma_zero_y")
stringarray_zero_y=($result_zero_y)
sig_zero_y=${stringarray_zero_y[2]}
sig_zero_y=${sig_zero_y/-/}
sig_zero_y_err=${stringarray_zero_y[4]}
MS=$(echo $ZEROFILE | tr -dc '0-9')
echo -e "$sig_zero_y" >> $TEMPOUTZERO_y
fi

#Remove local files
rm $FILE
rm $ZEROFILE


#Get mean zero position for x
echo -e "0\t"$(awk '{for(i=1;i<=NF;i++) {sum[i] += $i; sumsq[i] += ($i)^2}} 
          END {for (i=1;i<=NF;i++) {
          print sum[i]/NR, sqrt((sumsq[i]-sum[i]^2/NR)/NR)/sqrt(NR)}
         }' $TEMPOUTZERO_x) >> $TEMPOUT_x
DATA=output_$MOLASSES-x.txt #Append to output file
cp $TEMPOUT_x $DATA
DATA_ZERO_x=output_zeroes_$MOLASSES-x.txt #Store fits of zeros
cp $TEMPOUTZERO_x $DATA_ZERO_x
#Remove temporary files
rm $TEMPOUT_x
rm $TEMPOUTZERO_x
#Fit to temperature formula
gnuplot -e  "psname='Temperature_$DATA.ps';title='Molasses Time = $MOLASSES';datafile='$DATA';" Temperature.gnu
echo -e "$MOLASSES\t"$(grep "+/-" fit.log | grep "T") >> temperature_log_x.txt

#Get mean zero position for y
echo -e "0\t"$(awk '{for(i=1;i<=NF;i++) {sum[i] += $i; sumsq[i] += ($i)^2}} 
          END {for (i=1;i<=NF;i++) {
          print sum[i]/NR, sqrt((sumsq[i]-sum[i]^2/NR)/NR)/sqrt(NR)}
         }' $TEMPOUTZERO_y) >> $TEMPOUT_y
DATA=output_$MOLASSES-y.txt #Append to output file
cp $TEMPOUT_y $DATA
DATA_ZERO_y=output_zeroes_$MOLASSES-y.txt #Store fits of zeros
cp $TEMPOUTZERO_y $DATA_ZERO_y
#Remove temporary files
rm $TEMPOUT_y
rm $TEMPOUTZERO_y
#Fit to temperature formula
gnuplot -e  "psname='Temperature_$DATA.ps';title='Molasses Time = $MOLASSES';datafile='$DATA';" Temperature.gnu
echo -e "$MOLASSES\t"$(grep "+/-" fit.log | grep "T") >> temperature_log_y.txt


done #end loop over waiting times

#resultT=$(grep "+/-" fit.log | grep "T")
#stringarrayT=($resultT)
#sig_T=${stringarrayT[2]}
#sig_T=${sig_T/-/}
#sig_T_err=${stringarrayT[4]}
#MS_T=$(echo $MOLASSES | tr -dc '0-9')
#echo -e "$MS_T\t$sig_T\t$sig_T_err" >> Temperature_vs_molasses.txt
done #end loop over molasses times