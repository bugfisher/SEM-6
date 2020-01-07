package Weatherpackage;

import java.io.IOException;

import org.apache.hadoop.conf.Configuration;

import org.apache.hadoop.fs.Path;

import org.apache.hadoop.io.IntWritable;

import org.apache.hadoop.io.LongWritable;

import org.apache.hadoop.io.Text;

import org.apache.hadoop.mapreduce.Job;

import org.apache.hadoop.mapreduce.Mapper;

import org.apache.hadoop.mapreduce.Reducer;

import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;

import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

import org.apache.hadoop.util.GenericOptionsParser;



public class Weatherclass {
	
	public static void main(String [] args) throws Exception

	{

	Configuration c=new Configuration();

	String[] files=new GenericOptionsParser(c,args).getRemainingArgs();

	Path input=new Path(files[0]);

	Path output=new Path(files[1]);

	Job j=new Job(c,"wordcount");
	
	Job jj=new Job(c,"w1");

	j.setJarByClass(Weatherclass.class);

	j.setMapperClass(MapForWordCount.class);

	j.setReducerClass(ReduceForWordCount.class);
	

	j.setOutputKeyClass(Text.class);

	j.setOutputValueClass(IntWritable.class);

	FileInputFormat.addInputPath(j, input);

	FileOutputFormat.setOutputPath(j, output);

	System.exit(j.waitForCompletion(true)?0:1);

	}

	public static class MapForWordCount extends Mapper<LongWritable, Text, Text, IntWritable>{

	public void map(LongWritable key, Text value, Context con) throws IOException, InterruptedException

	{

	String line = value.toString();

	String year= line.substring(15, 19);
	
	String temp = line.substring(87, 92);
	
	int temperature = Integer.valueOf(temp);

	

	 Text outputKey = new Text(year);

	  IntWritable outputValue = new IntWritable(temperature);

	  con.write(outputKey, outputValue);

	

	}

	}

	public static class ReduceForWordCount extends Reducer<Text, IntWritable, Text, IntWritable>

	{
		Text[] year = new Text[50];
		int[] t = new int[50];
		int index=0;
		


	public void reduce(Text word, Iterable<IntWritable> values, Context con) throws IOException, InterruptedException

	{
		
	

	int sum = 0;
	int i=0;

	   for(IntWritable value : values)

	   {

		   sum += value.get();
		   i++;

	   }
	   sum = sum/i;

	   con.write(word, new IntWritable(sum));
	   year[index] = word;
	   t[index] = sum;
	   index++;
	   
	   
	  
	   

	}
	public void reduce1(Text word, Iterable<IntWritable> values, Context con) throws IOException, InterruptedException

	{
		 int max = getMax(t);
		 int min = getMin(t);
		 
		 con.write(year[max],new IntWritable(t[max]));
		 con.write(year[min], new IntWritable(t[min]));
		
		
		
		
		
	}
	 public static int getMax(int[] inputArray){ 
		    int maxValue = inputArray[0]; 
		    for(int i=1;i < inputArray.length;i++){ 
		      if(inputArray[i] > maxValue){ 
		         maxValue = i; 
		      } 
		    } 
		    return maxValue; 
		  }
		 
		  // Method for getting the minimum value
		  public static int getMin(int[] inputArray){ 
		    int minValue = inputArray[0]; 
		    for(int i=1;i<inputArray.length;i++){ 
		      if(inputArray[i] < minValue){ 
		        minValue = i; 
		      } 
		    } 
		    return minValue; 
		  } 
	

	}

}
