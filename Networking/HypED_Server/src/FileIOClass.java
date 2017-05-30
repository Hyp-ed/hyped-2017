
/*
 *       Title: HypED FileIOClass
 *       Autor: Jack Gargan
 * Description: A FileIO object will manage the File I/O required to facilitate
                the 'Save to File' functionality on the main GUI, which will 
                save the content of the console to a text file. This may prove 
                usefull with respect to isolating errors in pod operation.
 */

import java.io.*;
import java.util.ArrayList;
import javax.swing.*;

public class FileIOClass
{
	
	//-----------------------------------------------------------------------------------//
	// I-VAR DECLERATION & INITIALISATION                                                //
	//-----------------------------------------------------------------------------------//
	
	private FileReader _file = null;	
	private BufferedReader _reader = null;	
                                                        
	private FileWriter _output = null;  
	private BufferedWriter _writer = null;	
						
	private String _filePath = "";		
	private int _status = 0;    // Determine if error occurred, enabling calling code to 
                                    //  perform appropriate action.
	//-----------------------------------------------------------------------------------//
	// CONSTRUCTOR DECLERATION                                                           //
	//-----------------------------------------------------------------------------------//	
	
	public FileIOClass(){}	  // Blank constructor to init. file path at later convenience.
	
	public FileIOClass(String filePath){ this.setFilePath(filePath); }   // Init. filePath.
        
        public FileIOClass(String filePath, boolean create)
        {
            if (create) this.createFile();
            else this.setFilePath(filePath);
        }
        
	public void setFilePath(String filePath) { _filePath = filePath; this.openFile(); }
                      // Set filePath and open file. If filePath changed then pointers updated.
        
        public void setCreatePath(String filePath) { _filePath = filePath; this.createFile(); }
	
	//-----------------------------------------------------------------------------------//
	// OBJECT METHODS                                                                    //
	//-----------------------------------------------------------------------------------//

	// INITIALISE FILE COMPONENTS.
	private void openFile()
	{
		try                                                     // Exception handling.
		{
			_file = new FileReader(_filePath);
			_reader = new BufferedReader(_file);
		} catch (IOException e) { printError(e, "opening"); }	// Catch 'FileNotFound' 
	}                             // Exception and call 'printError' method to inform user.
	
	// DESTROY FILE OBJECTS - DANGLING POINTERS HANDLED BY JVM GARBAGE COLLECTOR.
	public void closeFile()
	{
		try                                                      // Exception handling.
		{
			_file.close();
			_reader.close();
		} catch (IOException e) { printError(e, "closing"); }	// Catch 'FileNotFound'
	}                             // Exception and call 'printError' method to inform user.
	
        public void createFile()
        {
            File f = new File(_filePath);
            try
            {
                if (f.createNewFile()) this.openFile();
                else JOptionPane.showMessageDialog(null, "Could not create file.");
            }
            catch (IOException e) { printError(e, "creating"); }
        }
        
	// READ CONTENT OF FILE AND RETURN AS ARRAYLIST.
	public ArrayList<String> readFile()
	{
		String input;
		ArrayList<String> data = new ArrayList<String>(); // ArrayList => no need to determine
                // file size to inform array length. [IN PROJECT WILL OVERLOAD FOR DIFFERENT DATA-
					// TYPES - GENERICS AND ARRAYS DON'T WORK WELL TOGETHER.]
		try							// Exception handling.
		{
			while ((input = _reader.readLine()) != null)  data.add(input);
		 // If the next line is not empty then add to ArrayList (Parse from String to Double).
		} catch (IOException e) { printError(e, "reading"); }  // Catch error and inform user.
		return data;	// Return ArrayList.
	}
	
	// WRITE DATA TO FILE.
	public void writeFile(String data[]) 	 // Accept string array argument to write to file.
	{
		try                                                         // Exception handling.
		{
			_output = new FileWriter(_filePath);             // Create writer objects.
			_writer = new BufferedWriter(_output);
			
			for (int i = 0; i < data.length; i++)   // Iterate for each element in input array.
			{
				_writer.write(data[i]);
				_writer.newLine();		// Take new line for each element.
				_writer.flush();			// Write changes to disk.
			}
			
			_output.close();                                 // Destroy writer objects.
			_writer.close();
		} catch (IOException e) { printError(e, "writing"); } // Catch exception and report to
	}								// user.
	
	// PRINT EXCEPTION AND INFORM USER WHERE IT OCCURRED.
	private void printError(IOException e, String type)
	{
		JOptionPane.showMessageDialog
                (
                        null, "\nAn error occurred when " + type + " file:" + e + "\n\nPlease try again."
                );
		_status = -1;
	}
	
	// RETURN VALUE OF STATUS.
	public int getStatus(){ return _status; }
	
	// RE-SET VALUE OF STATUS (TO ZERO).
	public void setStatus(int zero) { _status = zero; }
}