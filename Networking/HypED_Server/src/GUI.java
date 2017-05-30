
import java.awt.Color;
import javax.swing.UIManager;
import java.util.*;
import java.text.*;
import javax.swing.JFileChooser;
import java.io.*;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Jack_Gargan
 */
public class GUI extends javax.swing.JFrame {

    /**
     * Creates new form GUI
     */
    
    int batteryTempThreshold = 100,
        voltageThreshold = 100,
        currentThreshold = 50;
    
    public GUI() {
        try
        {
            UIManager.setLookAndFeel(
            UIManager.getCrossPlatformLookAndFeelClassName());
        } 
        catch (Exception e) 
        {
            //this.printToConsole(e.getMessage());
            System.err.print(e);
        }
        initComponents();
        setLocationRelativeTo(null);
        initConsole();
        
    }
    
    public static void initConsole()
    {
        // Set indentation for new linewraps
    }
    
    public static String getCurrentTimeStamp() 
    {
      SimpleDateFormat sdf = new SimpleDateFormat("HH:mm:ss.SSS");
       return sdf.format(new Date());
    }
    
    public void printToConsole(String message)
    {
        console.append(this.getCurrentTimeStamp() + ": " + message + "\n");
    }
    
    // Include colour management later... e.g. over THRESHOLD then RED text
    
    public void printAcceleration(int acceleration)
    {
        accelField.setText(Integer.toString(acceleration));
    }
    
    public void printPosition(int position)
    {
        positionField.setText(Integer.toString(position));
    }
    
    public void printPodTemperature(int temp)
    {
        tempField.setText(Integer.toString(temp));
    }
    
    public void printStripeCount(int count)
    {
        stripeField.setText(Integer.toString(count));
    }
    
    public void printBatteryTemperature(int temp)
    {
        if (temp < batteryTempThreshold) BatTempField.setForeground(new Color(0, 153, 51));
        else 
        {
            BatTempField.setForeground(Color.red);
            this.printToConsole("BATTERY TEMPERATURE OVER MAXIMUM THRESHOLD");
        }
        BatTempField.setText(Integer.toString(temp));
    }
    
    public void printVoltage(int voltage) 
    {
        if (voltage < voltageThreshold) voltageField.setForeground(new Color(0, 153, 51));
        else 
        {
            voltageField.setForeground(Color.red);
            this.printToConsole("BATTERY VOLTAGE OVER MAXIMUM THRESHOLD");
        }
        
        voltageField.setText(Integer.toString(voltage));
    }
    
    public void printCurrent(int current)
    {
        if (current < currentThreshold) currentField.setForeground(new Color(0, 153, 51));
        else 
        {
            currentField.setForeground(Color.red);
            this.printToConsole("BATTERY CURRENT OVER MAXIMUM THRESHOLD");
        }
        
        currentField.setText(Integer.toString(current));
    }
    
    public void setMasterOnline(boolean online)
    {
        if (online) 
        {
            masterField.setBackground(new Color(0,153,51));
            //this.printToConsole("MASTER PI CONNECTION ESTABLISHED");
        }
        else 
        {
            masterField.setBackground(Color.red);
            this.printToConsole("MASTER PI OFFLINE!");
        }
    }
    
    public void setSlave0Online(boolean online)
    {
        if (online) 
        {
            slave0Field.setBackground(new Color(0,153,51));
            //this.printToConsole("SLAVE_0 PI CONNECTION ESTABLISHED");
        }
        else 
        {
            slave0Field.setBackground(Color.red);
            this.printToConsole("SLAVE_0 PI OFFLINE!");
        }
    }
    
    public void setSlave1Online(boolean online)
    {
        if (online) 
        {
            slave1Field.setBackground(new Color(0,153,51));
            //this.printToConsole("SLAVE_1 PI CONNECTION ESTABLISHED");
        }
        else 
        {
            slave1Field.setBackground(Color.red);
            this.printToConsole("SLAVE_1 PI OFFLINE!");
        }
    }
    
    public void setSlave2Online(boolean online)
    {
        if (online) 
        {
            slave2Field.setBackground(new Color(0,153,51));
            //this.printToConsole("SLAVE_2 PI CONNECTION ESTABLISHED");
        }
        else 
        {
            slave2Field.setBackground(Color.red);
            this.printToConsole("SLAVE_2 PI OFFLINE!");
        }
    }
    
    public void setSlave3Online(boolean online)
    {
        if (online) 
        {
            slave3Field.setBackground(new Color(0,153,51));
            //this.printToConsole("SLAVE_3 PI CONNECTION ESTABLISHED");
        }
        else 
        {
            slave3Field.setBackground(Color.red);
            this.printToConsole("SLAVE_3 PI OFFLINE!");
        }
    }
    
    public void setPodStatus(int status)
    {
        podField.setText(Integer.toString(status));
        if (status == 0) 
        {
            podField.setForeground(Color.red);
             this.printToConsole("POD STATE: FAULT OCCURRED");
        }
        else podField.setForeground(new Color(0,153,51));
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jPanel1 = new javax.swing.JPanel();
        jLabel2 = new javax.swing.JLabel();
        currentField = new javax.swing.JTextField();
        jLabel4 = new javax.swing.JLabel();
        jLabel6 = new javax.swing.JLabel();
        jLabel7 = new javax.swing.JLabel();
        accelField = new javax.swing.JTextField();
        jLabel8 = new javax.swing.JLabel();
        positionField = new javax.swing.JTextField();
        jLabel5 = new javax.swing.JLabel();
        jLabel9 = new javax.swing.JLabel();
        jPanel2 = new javax.swing.JPanel();
        jLabel10 = new javax.swing.JLabel();
        velocityField1 = new javax.swing.JTextField();
        jLabel11 = new javax.swing.JLabel();
        jLabel12 = new javax.swing.JLabel();
        statusField1 = new javax.swing.JTextField();
        jLabel13 = new javax.swing.JLabel();
        jLabel14 = new javax.swing.JLabel();
        accelField1 = new javax.swing.JTextField();
        jLabel15 = new javax.swing.JLabel();
        positionField1 = new javax.swing.JTextField();
        jLabel16 = new javax.swing.JLabel();
        jLabel17 = new javax.swing.JLabel();
        jLabel18 = new javax.swing.JLabel();
        velocityField = new javax.swing.JTextField();
        jLabel19 = new javax.swing.JLabel();
        jLabel20 = new javax.swing.JLabel();
        tempField = new javax.swing.JTextField();
        jLabel21 = new javax.swing.JLabel();
        jLabel22 = new javax.swing.JLabel();
        jLabel23 = new javax.swing.JLabel();
        stripeField = new javax.swing.JTextField();
        jLabel24 = new javax.swing.JLabel();
        jLabel25 = new javax.swing.JLabel();
        BatTempField = new javax.swing.JTextField();
        jLabel26 = new javax.swing.JLabel();
        jLabel27 = new javax.swing.JLabel();
        voltageField = new javax.swing.JTextField();
        jLabel28 = new javax.swing.JLabel();
        jScrollPane1 = new javax.swing.JScrollPane();
        console = new javax.swing.JTextArea();
        jLabel29 = new javax.swing.JLabel();
        saveButton = new javax.swing.JButton();
        settingsButton = new javax.swing.JButton();
        masterField = new javax.swing.JTextField();
        jLabel30 = new javax.swing.JLabel();
        slave0Field = new javax.swing.JTextField();
        jLabel31 = new javax.swing.JLabel();
        slave1Field = new javax.swing.JTextField();
        jLabel32 = new javax.swing.JLabel();
        slave2Field = new javax.swing.JTextField();
        jLabel33 = new javax.swing.JLabel();
        podField = new javax.swing.JTextField();
        jLabel34 = new javax.swing.JLabel();
        slave3Field = new javax.swing.JTextField();
        jLabel35 = new javax.swing.JLabel();
        jLabel36 = new javax.swing.JLabel();
        jLabel1 = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("HypED – Poddy McPodface");
        setBackground(new java.awt.Color(0, 0, 153));
        setForeground(new java.awt.Color(51, 0, 102));
        setResizable(false);
        setSize(new java.awt.Dimension(29, 16));
        getContentPane().setLayout(new javax.swing.OverlayLayout(getContentPane()));

        jPanel1.setOpaque(false);
        jPanel1.setLayout(null);

        jLabel2.setFont(new java.awt.Font("Lucida Grande", 1, 18)); // NOI18N
        jLabel2.setForeground(new java.awt.Color(204, 204, 255));
        jLabel2.setText("stripes");
        jPanel1.add(jLabel2);
        jLabel2.setBounds(330, 280, 80, 20);

        currentField.setEditable(false);
        currentField.setBackground(new java.awt.Color(204, 204, 255));
        currentField.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        currentField.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        currentField.setText("LOADING...");
        currentField.setFocusable(false);
        jPanel1.add(currentField);
        currentField.setBounds(150, 450, 170, 20);

        jLabel4.setFont(new java.awt.Font("Lucida Grande", 1, 30)); // NOI18N
        jLabel4.setForeground(new java.awt.Color(255, 255, 255));
        jLabel4.setText("BATTERY DATA");
        jPanel1.add(jLabel4);
        jLabel4.setBounds(10, 330, 260, 30);

        jLabel6.setFont(new java.awt.Font("Lucida Grande", 1, 18)); // NOI18N
        jLabel6.setForeground(new java.awt.Color(204, 204, 255));
        jLabel6.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel6.setText("Current:");
        jPanel1.add(jLabel6);
        jLabel6.setBounds(-30, 450, 170, 20);

        jLabel7.setFont(new java.awt.Font("Lucida Grande", 1, 18)); // NOI18N
        jLabel7.setForeground(new java.awt.Color(204, 204, 255));
        jLabel7.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel7.setText("Acceleration:");
        jPanel1.add(jLabel7);
        jLabel7.setBounds(-30, 160, 170, 20);

        accelField.setEditable(false);
        accelField.setBackground(new java.awt.Color(204, 204, 255));
        accelField.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        accelField.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        accelField.setText("WAITING...");
        accelField.setFocusable(false);
        jPanel1.add(accelField);
        accelField.setBounds(150, 160, 170, 20);

        jLabel8.setFont(new java.awt.Font("Lucida Grande", 1, 18)); // NOI18N
        jLabel8.setForeground(new java.awt.Color(204, 204, 255));
        jLabel8.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel8.setText("Position:");
        jPanel1.add(jLabel8);
        jLabel8.setBounds(-30, 190, 170, 20);

        positionField.setEditable(false);
        positionField.setBackground(new java.awt.Color(204, 204, 255));
        positionField.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        positionField.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        positionField.setText("WAITING...");
        positionField.setFocusable(false);
        jPanel1.add(positionField);
        positionField.setBounds(150, 190, 170, 20);

        jLabel5.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        jLabel5.setForeground(new java.awt.Color(204, 204, 255));
        jLabel5.setText("MASTER");
        jPanel1.add(jLabel5);
        jLabel5.setBounds(430, 70, 80, 20);

        jLabel9.setFont(new java.awt.Font("Lucida Grande", 1, 18)); // NOI18N
        jLabel9.setForeground(new java.awt.Color(204, 204, 255));
        jLabel9.setText("cm");
        jPanel1.add(jLabel9);
        jLabel9.setBounds(330, 190, 30, 20);

        jPanel2.setOpaque(false);
        jPanel2.setLayout(null);

        jLabel10.setFont(new java.awt.Font("Lucida Grande", 1, 18)); // NOI18N
        jLabel10.setForeground(new java.awt.Color(204, 204, 255));
        jLabel10.setText("cm s^-1");
        jPanel2.add(jLabel10);
        jLabel10.setBounds(350, 220, 80, 20);

        velocityField1.setEditable(false);
        velocityField1.setBackground(new java.awt.Color(204, 204, 255));
        velocityField1.setFont(new java.awt.Font("Lucida Grande", 1, 18)); // NOI18N
        velocityField1.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        velocityField1.setText("1");
        jPanel2.add(velocityField1);
        velocityField1.setBounds(180, 220, 170, 20);

        jLabel11.setBackground(new java.awt.Color(255, 0, 0));
        jLabel11.setFont(new java.awt.Font("Lucida Grande", 1, 24)); // NOI18N
        jLabel11.setForeground(new java.awt.Color(255, 51, 51));
        jLabel11.setText("POD STATUS:");
        jPanel2.add(jLabel11);
        jLabel11.setBounds(670, 30, 180, 30);

        jLabel12.setFont(new java.awt.Font("Lucida Grande", 1, 30)); // NOI18N
        jLabel12.setForeground(new java.awt.Color(255, 255, 255));
        jLabel12.setText("POD DATA");
        jPanel2.add(jLabel12);
        jLabel12.setBounds(20, 110, 170, 30);

        statusField1.setEditable(false);
        statusField1.setBackground(new java.awt.Color(204, 204, 255));
        statusField1.setFont(new java.awt.Font("Lucida Grande", 1, 24)); // NOI18N
        statusField1.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        statusField1.setText("1");
        jPanel2.add(statusField1);
        statusField1.setBounds(850, 30, 60, 30);

        jLabel13.setFont(new java.awt.Font("Lucida Grande", 1, 18)); // NOI18N
        jLabel13.setForeground(new java.awt.Color(204, 204, 255));
        jLabel13.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel13.setText("Velocity:");
        jPanel2.add(jLabel13);
        jLabel13.setBounds(10, 220, 170, 20);

        jLabel14.setFont(new java.awt.Font("Lucida Grande", 1, 18)); // NOI18N
        jLabel14.setForeground(new java.awt.Color(204, 204, 255));
        jLabel14.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel14.setText("Acceleration:");
        jPanel2.add(jLabel14);
        jLabel14.setBounds(10, 160, 170, 20);

        accelField1.setEditable(false);
        accelField1.setBackground(new java.awt.Color(204, 204, 255));
        accelField1.setFont(new java.awt.Font("Lucida Grande", 1, 18)); // NOI18N
        accelField1.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        accelField1.setText("1");
        jPanel2.add(accelField1);
        accelField1.setBounds(180, 160, 170, 20);

        jLabel15.setFont(new java.awt.Font("Lucida Grande", 1, 18)); // NOI18N
        jLabel15.setForeground(new java.awt.Color(204, 204, 255));
        jLabel15.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel15.setText("Position:");
        jPanel2.add(jLabel15);
        jLabel15.setBounds(10, 190, 170, 20);

        positionField1.setEditable(false);
        positionField1.setBackground(new java.awt.Color(204, 204, 255));
        positionField1.setFont(new java.awt.Font("Lucida Grande", 1, 18)); // NOI18N
        positionField1.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        positionField1.setText("1");
        jPanel2.add(positionField1);
        positionField1.setBounds(180, 190, 170, 20);

        jLabel16.setFont(new java.awt.Font("Lucida Grande", 1, 18)); // NOI18N
        jLabel16.setForeground(new java.awt.Color(204, 204, 255));
        jLabel16.setText("cm s^-2");
        jPanel2.add(jLabel16);
        jLabel16.setBounds(350, 160, 80, 20);

        jLabel17.setFont(new java.awt.Font("Lucida Grande", 1, 18)); // NOI18N
        jLabel17.setForeground(new java.awt.Color(204, 204, 255));
        jLabel17.setText("cm");
        jPanel2.add(jLabel17);
        jLabel17.setBounds(350, 190, 30, 20);

        jPanel1.add(jPanel2);
        jPanel2.setBounds(0, 0, 0, 0);

        jLabel18.setFont(new java.awt.Font("Lucida Grande", 1, 18)); // NOI18N
        jLabel18.setForeground(new java.awt.Color(204, 204, 255));
        jLabel18.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel18.setText("Velocity:");
        jPanel1.add(jLabel18);
        jLabel18.setBounds(-30, 220, 170, 20);

        velocityField.setEditable(false);
        velocityField.setBackground(new java.awt.Color(204, 204, 255));
        velocityField.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        velocityField.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        velocityField.setText("WAITING...");
        velocityField.setFocusable(false);
        jPanel1.add(velocityField);
        velocityField.setBounds(150, 220, 170, 20);

        jLabel19.setFont(new java.awt.Font("Lucida Grande", 1, 18)); // NOI18N
        jLabel19.setForeground(new java.awt.Color(204, 204, 255));
        jLabel19.setText("cm s^-1");
        jPanel1.add(jLabel19);
        jLabel19.setBounds(330, 220, 80, 20);

        jLabel20.setFont(new java.awt.Font("Lucida Grande", 1, 18)); // NOI18N
        jLabel20.setForeground(new java.awt.Color(204, 204, 255));
        jLabel20.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel20.setText("Temperature:");
        jPanel1.add(jLabel20);
        jLabel20.setBounds(-30, 250, 170, 20);

        tempField.setEditable(false);
        tempField.setBackground(new java.awt.Color(204, 204, 255));
        tempField.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        tempField.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        tempField.setText("WAITING...");
        tempField.setFocusable(false);
        jPanel1.add(tempField);
        tempField.setBounds(150, 250, 170, 20);

        jLabel21.setFont(new java.awt.Font("Lucida Grande", 1, 18)); // NOI18N
        jLabel21.setForeground(new java.awt.Color(204, 204, 255));
        jLabel21.setText("mA");
        jPanel1.add(jLabel21);
        jLabel21.setBounds(330, 450, 80, 20);

        jLabel22.setFont(new java.awt.Font("Lucida Grande", 1, 30)); // NOI18N
        jLabel22.setForeground(new java.awt.Color(255, 255, 255));
        jLabel22.setText("CONSOLE");
        jPanel1.add(jLabel22);
        jLabel22.setBounds(430, 110, 170, 30);

        jLabel23.setFont(new java.awt.Font("Lucida Grande", 1, 18)); // NOI18N
        jLabel23.setForeground(new java.awt.Color(204, 204, 255));
        jLabel23.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel23.setText("Stripe Count:");
        jPanel1.add(jLabel23);
        jLabel23.setBounds(-30, 280, 170, 20);

        stripeField.setEditable(false);
        stripeField.setBackground(new java.awt.Color(204, 204, 255));
        stripeField.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        stripeField.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        stripeField.setText("WAITING...");
        stripeField.setFocusable(false);
        jPanel1.add(stripeField);
        stripeField.setBounds(150, 280, 170, 20);

        jLabel24.setFont(new java.awt.Font("Lucida Grande", 1, 18)); // NOI18N
        jLabel24.setForeground(new java.awt.Color(204, 204, 255));
        jLabel24.setText("°C / 10");
        jPanel1.add(jLabel24);
        jLabel24.setBounds(330, 250, 80, 20);

        jLabel25.setFont(new java.awt.Font("Lucida Grande", 1, 18)); // NOI18N
        jLabel25.setForeground(new java.awt.Color(204, 204, 255));
        jLabel25.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel25.setText("Temperature:");
        jPanel1.add(jLabel25);
        jLabel25.setBounds(-30, 390, 170, 20);

        BatTempField.setEditable(false);
        BatTempField.setBackground(new java.awt.Color(204, 204, 255));
        BatTempField.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        BatTempField.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        BatTempField.setText("LOADING...");
        BatTempField.setFocusable(false);
        jPanel1.add(BatTempField);
        BatTempField.setBounds(150, 390, 170, 20);

        jLabel26.setFont(new java.awt.Font("Lucida Grande", 1, 18)); // NOI18N
        jLabel26.setForeground(new java.awt.Color(204, 204, 255));
        jLabel26.setText("°C / 10");
        jPanel1.add(jLabel26);
        jLabel26.setBounds(330, 390, 80, 20);

        jLabel27.setFont(new java.awt.Font("Lucida Grande", 1, 18)); // NOI18N
        jLabel27.setForeground(new java.awt.Color(204, 204, 255));
        jLabel27.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel27.setText("Voltage:");
        jPanel1.add(jLabel27);
        jLabel27.setBounds(-30, 420, 170, 20);

        voltageField.setEditable(false);
        voltageField.setBackground(new java.awt.Color(204, 204, 255));
        voltageField.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        voltageField.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        voltageField.setText("LOADING...");
        voltageField.setFocusable(false);
        jPanel1.add(voltageField);
        voltageField.setBounds(150, 420, 170, 20);

        jLabel28.setFont(new java.awt.Font("Lucida Grande", 1, 18)); // NOI18N
        jLabel28.setForeground(new java.awt.Color(204, 204, 255));
        jLabel28.setText("mV");
        jPanel1.add(jLabel28);
        jLabel28.setBounds(330, 420, 80, 20);

        console.setEditable(false);
        console.setBackground(new java.awt.Color(204, 204, 255));
        console.setColumns(20);
        console.setFont(new java.awt.Font("Lucida Grande", 0, 18)); // NOI18N
        console.setForeground(new java.awt.Color(0, 0, 153));
        console.setLineWrap(true);
        console.setRows(5);
        console.setWrapStyleWord(true);
        console.setFocusable(false);
        jScrollPane1.setViewportView(console);

        jPanel1.add(jScrollPane1);
        jScrollPane1.setBounds(430, 160, 520, 310);

        jLabel29.setFont(new java.awt.Font("Lucida Grande", 1, 30)); // NOI18N
        jLabel29.setForeground(new java.awt.Color(255, 255, 255));
        jLabel29.setText("POD DATA");
        jPanel1.add(jLabel29);
        jLabel29.setBounds(20, 110, 170, 30);

        saveButton.setText("Save to File...");
        saveButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                saveButtonActionPerformed(evt);
            }
        });
        jPanel1.add(saveButton);
        saveButton.setBounds(820, 490, 130, 29);

        settingsButton.setText("Network Settings...");
        jPanel1.add(settingsButton);
        settingsButton.setBounds(430, 490, 150, 29);

        masterField.setEditable(false);
        masterField.setBackground(new java.awt.Color(255, 51, 51));
        masterField.setFocusable(false);
        jPanel1.add(masterField);
        masterField.setBounds(440, 20, 50, 40);

        jLabel30.setFont(new java.awt.Font("Lucida Grande", 1, 18)); // NOI18N
        jLabel30.setForeground(new java.awt.Color(204, 204, 255));
        jLabel30.setText("cm s^-2");
        jPanel1.add(jLabel30);
        jLabel30.setBounds(330, 160, 80, 20);

        slave0Field.setEditable(false);
        slave0Field.setBackground(new java.awt.Color(255, 51, 51));
        slave0Field.setFocusable(false);
        jPanel1.add(slave0Field);
        slave0Field.setBounds(530, 20, 50, 40);

        jLabel31.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        jLabel31.setForeground(new java.awt.Color(204, 204, 255));
        jLabel31.setText("SLAVE 0");
        jPanel1.add(jLabel31);
        jLabel31.setBounds(520, 70, 80, 20);

        slave1Field.setEditable(false);
        slave1Field.setBackground(new java.awt.Color(255, 51, 51));
        slave1Field.setFocusable(false);
        jPanel1.add(slave1Field);
        slave1Field.setBounds(620, 20, 50, 40);

        jLabel32.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        jLabel32.setForeground(new java.awt.Color(204, 204, 255));
        jLabel32.setText("SLAVE 1");
        jPanel1.add(jLabel32);
        jLabel32.setBounds(610, 70, 80, 20);

        slave2Field.setEditable(false);
        slave2Field.setBackground(new java.awt.Color(255, 51, 51));
        slave2Field.setFocusable(false);
        jPanel1.add(slave2Field);
        slave2Field.setBounds(710, 20, 50, 40);

        jLabel33.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        jLabel33.setForeground(new java.awt.Color(204, 204, 255));
        jLabel33.setText("SLAVE 2");
        jPanel1.add(jLabel33);
        jLabel33.setBounds(700, 70, 80, 20);

        podField.setEditable(false);
        podField.setBackground(new java.awt.Color(204, 204, 255));
        podField.setFont(new java.awt.Font("Lucida Grande", 1, 24)); // NOI18N
        podField.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        podField.setFocusable(false);
        jPanel1.add(podField);
        podField.setBounds(880, 20, 50, 40);

        jLabel34.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        jLabel34.setForeground(new java.awt.Color(204, 204, 255));
        jLabel34.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel34.setText("STATUS");
        jLabel34.setFocusable(false);
        jPanel1.add(jLabel34);
        jLabel34.setBounds(870, 90, 70, 20);

        slave3Field.setEditable(false);
        slave3Field.setBackground(new java.awt.Color(255, 51, 51));
        slave3Field.setFocusable(false);
        jPanel1.add(slave3Field);
        slave3Field.setBounds(800, 20, 50, 40);

        jLabel35.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        jLabel35.setForeground(new java.awt.Color(204, 204, 255));
        jLabel35.setText("SLAVE 3");
        jPanel1.add(jLabel35);
        jLabel35.setBounds(790, 70, 80, 20);

        jLabel36.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        jLabel36.setForeground(new java.awt.Color(204, 204, 255));
        jLabel36.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel36.setText("POD");
        jLabel36.setFocusable(false);
        jPanel1.add(jLabel36);
        jLabel36.setBounds(880, 70, 50, 20);

        getContentPane().add(jPanel1);

        jLabel1.setIcon(new javax.swing.ImageIcon(getClass().getResource("/Background.png"))); // NOI18N
        getContentPane().add(jLabel1);

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void saveButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_saveButtonActionPerformed

        String desktop = System.getProperty ("user.home") + "/Desktop/";
        FileIOClass fileObj = new FileIOClass();
        fileObj.setCreatePath(desktop + this.getCurrentTimeStamp() + ".txt");
        fileObj.writeFile(console.getText().split("\n"));
        this.printToConsole("CONSOLE LOG SAVED TO DESKTOP");
    }//GEN-LAST:event_saveButtonActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Metal".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(GUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(GUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(GUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(GUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new GUI().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JTextField BatTempField;
    private javax.swing.JTextField accelField;
    private javax.swing.JTextField accelField1;
    private javax.swing.JTextArea console;
    private javax.swing.JTextField currentField;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel10;
    private javax.swing.JLabel jLabel11;
    private javax.swing.JLabel jLabel12;
    private javax.swing.JLabel jLabel13;
    private javax.swing.JLabel jLabel14;
    private javax.swing.JLabel jLabel15;
    private javax.swing.JLabel jLabel16;
    private javax.swing.JLabel jLabel17;
    private javax.swing.JLabel jLabel18;
    private javax.swing.JLabel jLabel19;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel20;
    private javax.swing.JLabel jLabel21;
    private javax.swing.JLabel jLabel22;
    private javax.swing.JLabel jLabel23;
    private javax.swing.JLabel jLabel24;
    private javax.swing.JLabel jLabel25;
    private javax.swing.JLabel jLabel26;
    private javax.swing.JLabel jLabel27;
    private javax.swing.JLabel jLabel28;
    private javax.swing.JLabel jLabel29;
    private javax.swing.JLabel jLabel30;
    private javax.swing.JLabel jLabel31;
    private javax.swing.JLabel jLabel32;
    private javax.swing.JLabel jLabel33;
    private javax.swing.JLabel jLabel34;
    private javax.swing.JLabel jLabel35;
    private javax.swing.JLabel jLabel36;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JLabel jLabel6;
    private javax.swing.JLabel jLabel7;
    private javax.swing.JLabel jLabel8;
    private javax.swing.JLabel jLabel9;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel2;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JTextField masterField;
    private javax.swing.JTextField podField;
    private javax.swing.JTextField positionField;
    private javax.swing.JTextField positionField1;
    private javax.swing.JButton saveButton;
    private javax.swing.JButton settingsButton;
    private javax.swing.JTextField slave0Field;
    private javax.swing.JTextField slave1Field;
    private javax.swing.JTextField slave2Field;
    private javax.swing.JTextField slave3Field;
    private javax.swing.JTextField statusField1;
    private javax.swing.JTextField stripeField;
    private javax.swing.JTextField tempField;
    private javax.swing.JTextField velocityField;
    private javax.swing.JTextField velocityField1;
    private javax.swing.JTextField voltageField;
    // End of variables declaration//GEN-END:variables
}
