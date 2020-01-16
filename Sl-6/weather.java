package Weatherpackage;
import org.apache.hadoop.mapreduce.Job;  
import org.apache.hadoop.mapreduce.Mapper;  
import org.apache.hadoop.mapreduce.Reducer;

import java.io.IOException;
import java.util.Iterator;

import org.apache.hadoop.conf.Configuration;

import org.apache.hadoop.fs.Path;

import org.apache.hadoop.io.IntWritable;

import org.apache.hadoop.io.LongWritable;

import org.apache.hadoop.io.Text;

import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;

import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

import org.apache.hadoop.util.GenericOptionsParser;



public class Weatherclass {
	
	public static void main(String [] args) throws Exception

	{

	Configuration c=new Configuration();

	String[] files=new GenericOptionsParser(c,args).getRemainingArgs();

	Path input=new Path(files[0]);

	//Path output=new Path(files[1]);
	Path output=new Path("FirstMapper");

	Job j=new Job(c,"wordcount");
	

	j.setJarByClass(Weatherclass.class);

	j.setMapperClass(MapForWordCount.class);

	j.setReducerClass(ReduceForWordCount.class);
	
	j.setMapOutputKeyClass(Text.class);
	j.setMapOutputValueClass(IntWritable.class);
	

	j.setOutputKeyClass(Text.class);

	j.setOutputValueClass(IntWritable.class);

	FileInputFormat.addInputPath(j, input);

	FileOutputFormat.setOutputPath(j, output);
	//output.getFileSystem(c).delete(output);

	j.waitForCompletion(true);
	
	 Configuration conf2=new Configuration();
	 
	 Path output1=new Path(files[1]);
	 
	 Job j2=new Job(conf2,"wordcount1");
	 
     j2.setJarByClass(Weatherclass.class);
     
     j2.setMapperClass(MapForWordCount1.class);
     
     j2.setReducerClass(ReduceForWordCount1.class);
     
     j2.setMapOutputKeyClass(Text.class);
     j2.setMapOutputValueClass(IntWritable.class);
     
     j2.setOutputKeyClass(Text.class);
     
     j2.setOutputValueClass(IntWritable.class);
     
     FileInputFormat.addInputPath(j2, output);
     
     FileOutputFormat.setOutputPath(j2, output1);
     
     System.exit(j2.waitForCompletion(true)?0:1);
     
	

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
	   

	   con.write(new Text(word), new IntWritable(sum));
	   
	   
	  
	   

	}
	
	

}
	
	public static class MapForWordCount1 extends Mapper<Text, Text, Text, IntWritable>{
		
		/*String[] y = new String[40];
		int[] t = new int[40];
		int i=0;*/

		public void map1(Text key, Text value, Context con) throws IOException, InterruptedException

		{
			String line = value.toString();
			
			String[] split = line.split("\\s+");
			
			int temperature = Integer.valueOf(split[1]);
			
			Text key1 = new Text(split[0]);
			IntWritable pair = new IntWritable(temperature);

			
			con.write(key1, pair);
			
			
			
			
			

			
		

		}

		}
	
	public static class ReduceForWordCount1 extends Reducer<Text, IntWritable, Text, IntWritable>

	{
		
		


	public void reduce1(Text word, Iterable<IntWritable> values, Context con) throws IOException, InterruptedException

	{
		Iterator<IntWritable> iterator = values.iterator();
		
		int min = Integer.MAX_VALUE, max = 0;
		
		while (iterator.hasNext()) {

			int value = iterator.next().get();

			if (value < min) { 

			min = value;

			}

			if (value > max) { 

			max = value;

			}
			}
		
		con.write(word, new IntWritable(min));
		
		
		
		
		
	

	
	  
	   
	  
	   

	}
	}
	
	


}

