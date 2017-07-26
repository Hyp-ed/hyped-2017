
import java.awt.Color;
import javax.swing.UIManager;
import java.util.*;
import java.text.*;
import javax.swing.JFileChooser;
import java.io.*;
import javax.swing.JOptionPane;

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
    
    private static ConsoleWindow consoleWindow = new ConsoleWindow();
    private static NetworkSettings  settingsWindow = new NetworkSettings();
    private static Server parentPointer = null;
    
    double batteryTempThreshold = 70,
        bigBatMinVoltage = 17.5,
        bigBatMaxVoltage = 29.4,
        currentThreshold = 120,
        smallBatMaxvoltage = 21,
        smallBatMinVoltage = 12.5;
    
    public GUI(/*Server parent*/) {
        try
        {
            //this.parentPointer = parent;
            UIManager.setLookAndFeel(
            UIManager.getCrossPlatformLookAndFeelClassName());
            //jScrollPane1.setVisible(false);
            //console.setVisible(false);
        } 
        catch (Exception e) 
        {
            //this.printToConsole(e.getMessage());
            System.err.print(e);
        }
        initComponents();
        setLocationRelativeTo(null);
        
    }
    
    public void setParent(Server parent) { this.parentPointer = parent; }
    
    public static String getCurrentTimeStamp() 
    {
      SimpleDateFormat sdf = new SimpleDateFormat("HH:mm:ss.SSS");
       return sdf.format(new Date());
    }
    
    public void printToConsole(String message)
    {
        //console.append(this.getCurrentTimeStamp() + ": " + message + "\n");
        consoleWindow.print(this.getCurrentTimeStamp() + ": " + message + "\n");
    }
    
    // Include colour management later... e.g. over THRESHOLD then RED text
    
    public void printAcceleration(double acceleration)
    {
        accelField.setText(Double.toString(acceleration));
    }
    
    public void printVelocity(double velocity)
    {
        velocityField.setText(Double.toString(velocity));
    }
    
    public void printPosition(double position)
    {
        positionField.setText(Double.toString(position));
    }
    
    public void printPodTemperature(double temp)
    {
        tempField.setText(Double.toString(temp));
    }
    
    public void printStripeCount(double count)
    {
        stripeField.setText(Double.toString(count));
    }
    
    public void printBattery1Temperature(double temp)
    {
        if (temp < batteryTempThreshold) Bat1TempField.setForeground(new Color(0, 153, 51));
        else 
        {
            Bat1TempField.setForeground(Color.red);
            this.printToConsole("BATTERY 1 TEMPERATURE OVER MAXIMUM THRESHOLD");
        }
        Bat1TempField.setText(Double.toString(temp));
    }
    
    public void printBattery1Voltage(double voltage) 
    { 
        if (voltage < bigBatMinVoltage)
        {
            bat1VoltageField.setForeground(Color.red);
            this.printToConsole("BATTERY 1 VOLTAGE UNDER MINIMUM THRESHOLD");
        }
        else if (voltage > bigBatMaxVoltage)
        {
            bat1VoltageField.setForeground(Color.red);
            this.printToConsole("BATTERY 1 VOLTAGE OVER MAXIMUM THRESHOLD");
        }
        else  bat1VoltageField.setForeground(new Color(0, 153, 51));
        
        bat1VoltageField.setText(Double.toString(voltage));
    }
    
    public void printBattery1Current(double current)
    {
        if (current < currentThreshold) bat1CurrentField.setForeground(new Color(0, 153, 51));
        else 
        {
            bat1CurrentField.setForeground(Color.red);
            this.printToConsole("BATTERY 1 CURRENT OVER MAXIMUM THRESHOLD");
        }
        
        bat1CurrentField.setText(Double.toString(current));
    }
    
    public void printGroundProximity(double proximity)
    {
        groundProximityField.setText(Double.toString(proximity));
    }
    
    public void printRailProximity(double proximity)
    {
        railProximityField.setText(Double.toString(proximity));
    }
    
    public void printPusherDetection(int present)
    {
        if (present == 1)
        {
            pusherField.setText("YES");
            pusherField.setForeground(new Color(0, 153, 51));
        }
        else
        {
            pusherField.setText("NO");
            pusherField.setForeground(Color.red);
        }
        
    }
    
    public void printBattery2Temperature(double temp)
    {
        if (temp < batteryTempThreshold) Bat2TempField.setForeground(new Color(0, 153, 51));
        else 
        {
            Bat2TempField.setForeground(Color.red);
            this.printToConsole("BATTERY 2 TEMPERATURE OVER MAXIMUM THRESHOLD");
        }
        Bat2TempField.setText(Double.toString(temp));
    }
    
    public void printBattery2Current(double current)
    {
        if (current < currentThreshold) bat2CurrentField.setForeground(new Color(0, 153, 51));
        else 
        {
            bat2CurrentField.setForeground(Color.red);
            this.printToConsole("BATTERY 2 CURRENT OVER MAXIMUM THRESHOLD");
        }
        bat2CurrentField.setText(Double.toString(current));
    }
    
    public void printBattery2Voltage(double voltage)
    {
        if (voltage < bigBatMinVoltage)
        {
            bat2VoltageField.setForeground(Color.red);
            this.printToConsole("BATTERY 2 VOLTAGE UNDER MINIMUM THRESHOLD");
        }
        else if (voltage > bigBatMaxVoltage)
        {
            bat2VoltageField.setForeground(Color.red);
            this.printToConsole("BATTERY 2 VOLTAGE OVER MAXIMUM THRESHOLD");
        }
        else  bat2VoltageField.setForeground(new Color(0, 153, 51));
        
        bat2VoltageField.setText(Double.toString(voltage));
    }
    
    public void printBattery3Temperature(double temp)
    {
        if (temp < batteryTempThreshold) Bat3TempField.setForeground(new Color(0, 153, 51));
        else 
        {
            Bat3TempField.setForeground(Color.red);
            this.printToConsole("BATTERY 3 TEMPERATURE OVER MAXIMUM THRESHOLD");
        }
        Bat3TempField.setText(Double.toString(temp));
    }
    
    public void printBattery3Voltage(double voltage)
    {
        if (voltage < bigBatMinVoltage)
        {
            bat3VoltageField.setForeground(Color.red);
            this.printToConsole("BATTERY 3 VOLTAGE UNDER MINIMUM THRESHOLD");
        }
        else if (voltage > bigBatMaxVoltage)
        {
            bat3VoltageField.setForeground(Color.red);
            this.printToConsole("BATTERY 3 VOLTAGE OVER MAXIMUM THRESHOLD");
        }
        else  bat3VoltageField.setForeground(new Color(0, 153, 51));
        
        bat3VoltageField.setText(Double.toString(voltage));
    }
    
    public void printHydraulicState(int state)
    {
        // Include threshold colouring...
        if (state == 1) hydraulicStateField.setText("ACTUATED");
        else hydraulicStateField.setText("OFF");
    }
    
    public void printAccum1(int nominal)
    {
        // Pod should send 1 if nominal, 0 otherwise
        if (nominal == 1)
        {
            accum1Field.setText("NOMINAL");
            accum1Field.setForeground(new Color(0, 153, 51));
        }
        else
        {
            accum1Field.setText("HIGH!");
            accum1Field.setForeground(Color.red);
        }
    }
    
    public void printAccum2(int nominal)
    {
        // Pod should send 1 if nominal, 0 otherwise
        if (nominal == 1)
        {
            accum2Field.setText("NOMINAL");
            accum2Field.setForeground(new Color(0, 153, 51));
        }
        else
        {
            accum2Field.setText("HIGH!");
            accum2Field.setForeground(Color.red);
        }
    }
    
    public void printAccum3(int nominal)
    {
        // Pod should send 1 if nominal, 0 otherwise
        if (nominal == 1)
        {
            accum3Field.setText("NOMINAL");
            accum3Field.setForeground(new Color(0, 153, 51));
        }
        else
        {
            accum3Field.setText("HIGH!");
            accum3Field.setForeground(Color.red);
        }
    }
    
    public void printAccum4(int nominal)
    {
        // Pod should send 1 if nominal, 0 otherwise
        if (nominal == 1)
        {
            accum4Field.setText("NOMINAL");
            accum4Field.setForeground(new Color(0, 153, 51));
        }
        else
        {
            accum4Field.setText("HIGH!");
            accum4Field.setForeground(Color.red);
        }
    }
    
    public int getBasePort() { return settingsWindow.getBasePort(); }
    
    public int getSpaceXPort() { return settingsWindow.getSpaceXPort(); }
    
    public String getSpaceXIP() { return settingsWindow.getSpaceXIP(); }
    
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
             JOptionPane.showMessageDialog(null, "WARNING: POD ENTERED FAULT STATE.");
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
        bat1CurrentField = new javax.swing.JTextField();
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
        Bat1TempField = new javax.swing.JTextField();
        jLabel26 = new javax.swing.JLabel();
        jLabel27 = new javax.swing.JLabel();
        bat1VoltageField = new javax.swing.JTextField();
        jLabel28 = new javax.swing.JLabel();
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
        launchConsole = new javax.swing.JButton();
        groundProximityField = new javax.swing.JTextField();
        jLabel37 = new javax.swing.JLabel();
        jLabel3 = new javax.swing.JLabel();
        jLabel38 = new javax.swing.JLabel();
        railProximityField = new javax.swing.JTextField();
        jLabel39 = new javax.swing.JLabel();
        jLabel40 = new javax.swing.JLabel();
        pusherField = new javax.swing.JTextField();
        jLabel41 = new javax.swing.JLabel();
        jLabel42 = new javax.swing.JLabel();
        jLabel43 = new javax.swing.JLabel();
        jLabel44 = new javax.swing.JLabel();
        jLabel45 = new javax.swing.JLabel();
        Bat2TempField = new javax.swing.JTextField();
        jLabel46 = new javax.swing.JLabel();
        jLabel25 = new javax.swing.JLabel();
        bat2CurrentField = new javax.swing.JTextField();
        jLabel47 = new javax.swing.JLabel();
        jLabel48 = new javax.swing.JLabel();
        bat2VoltageField = new javax.swing.JTextField();
        jLabel49 = new javax.swing.JLabel();
        jLabel50 = new javax.swing.JLabel();
        jLabel51 = new javax.swing.JLabel();
        Bat3TempField = new javax.swing.JTextField();
        jLabel52 = new javax.swing.JLabel();
        jLabel53 = new javax.swing.JLabel();
        bat3VoltageField = new javax.swing.JTextField();
        jLabel54 = new javax.swing.JLabel();
        jLabel55 = new javax.swing.JLabel();
        jLabel56 = new javax.swing.JLabel();
        readyButton = new javax.swing.JButton();
        jLabel57 = new javax.swing.JLabel();
        jLabel58 = new javax.swing.JLabel();
        accum1Field = new javax.swing.JTextField();
        jLabel60 = new javax.swing.JLabel();
        accum2Field = new javax.swing.JTextField();
        jLabel61 = new javax.swing.JLabel();
        accum3Field = new javax.swing.JTextField();
        jLabel62 = new javax.swing.JLabel();
        accum4Field = new javax.swing.JTextField();
        brakeButton = new javax.swing.JButton();
        killPowerButton1 = new javax.swing.JButton();
        jLabel59 = new javax.swing.JLabel();
        hydraulicStateField = new javax.swing.JTextField();
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

        jLabel2.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel2.setForeground(new java.awt.Color(204, 204, 255));
        jLabel2.setText("mm");
        jPanel1.add(jLabel2);
        jLabel2.setBounds(270, 370, 80, 20);

        bat1CurrentField.setEditable(false);
        bat1CurrentField.setBackground(new java.awt.Color(204, 204, 255));
        bat1CurrentField.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        bat1CurrentField.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        bat1CurrentField.setText("WAITING...");
        bat1CurrentField.setFocusable(false);
        jPanel1.add(bat1CurrentField);
        bat1CurrentField.setBounds(480, 210, 110, 20);

        jLabel4.setFont(new java.awt.Font("Lucida Grande", 1, 26)); // NOI18N
        jLabel4.setForeground(new java.awt.Color(255, 255, 255));
        jLabel4.setText("HYDRAULIC DATA");
        jPanel1.add(jLabel4);
        jLabel4.setBounds(700, 110, 260, 30);

        jLabel6.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel6.setForeground(new java.awt.Color(204, 204, 255));
        jLabel6.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel6.setText("Current:");
        jPanel1.add(jLabel6);
        jLabel6.setBounds(360, 210, 110, 20);

        jLabel7.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
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
        accelField.setBounds(150, 160, 110, 20);

        jLabel8.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel8.setForeground(new java.awt.Color(204, 204, 255));
        jLabel8.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel8.setText("Position:");
        jPanel1.add(jLabel8);
        jLabel8.setBounds(-30, 220, 170, 20);

        positionField.setEditable(false);
        positionField.setBackground(new java.awt.Color(204, 204, 255));
        positionField.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        positionField.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        positionField.setText("WAITING...");
        positionField.setFocusable(false);
        jPanel1.add(positionField);
        positionField.setBounds(150, 220, 110, 20);

        jLabel5.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel5.setForeground(new java.awt.Color(204, 204, 255));
        jLabel5.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel5.setText("MASTER");
        jPanel1.add(jLabel5);
        jLabel5.setBounds(370, 60, 60, 20);

        jLabel9.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel9.setForeground(new java.awt.Color(204, 204, 255));
        jLabel9.setText("cm");
        jPanel1.add(jLabel9);
        jLabel9.setBounds(270, 220, 30, 20);

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

        jLabel18.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel18.setForeground(new java.awt.Color(204, 204, 255));
        jLabel18.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel18.setText("Velocity:");
        jPanel1.add(jLabel18);
        jLabel18.setBounds(-30, 190, 170, 20);

        velocityField.setEditable(false);
        velocityField.setBackground(new java.awt.Color(204, 204, 255));
        velocityField.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        velocityField.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        velocityField.setText("WAITING...");
        velocityField.setFocusable(false);
        jPanel1.add(velocityField);
        velocityField.setBounds(150, 190, 110, 20);

        jLabel19.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel19.setForeground(new java.awt.Color(204, 204, 255));
        jLabel19.setText("cm s^-1");
        jPanel1.add(jLabel19);
        jLabel19.setBounds(270, 190, 80, 20);

        jLabel20.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
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
        tempField.setBounds(150, 250, 110, 20);

        jLabel21.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel21.setForeground(new java.awt.Color(204, 204, 255));
        jLabel21.setText("mA");
        jPanel1.add(jLabel21);
        jLabel21.setBounds(600, 210, 80, 20);

        jLabel22.setFont(new java.awt.Font("Lucida Grande", 1, 26)); // NOI18N
        jLabel22.setForeground(new java.awt.Color(255, 255, 255));
        jLabel22.setHorizontalAlignment(javax.swing.SwingConstants.LEFT);
        jLabel22.setText("CMD PROMPT");
        jPanel1.add(jLabel22);
        jLabel22.setBounds(700, 340, 200, 30);

        jLabel23.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel23.setForeground(new java.awt.Color(204, 204, 255));
        jLabel23.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel23.setText("Ground Proximity:");
        jPanel1.add(jLabel23);
        jLabel23.setBounds(-30, 370, 170, 20);

        stripeField.setEditable(false);
        stripeField.setBackground(new java.awt.Color(204, 204, 255));
        stripeField.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        stripeField.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        stripeField.setText("WAITING...");
        stripeField.setFocusable(false);
        jPanel1.add(stripeField);
        stripeField.setBounds(150, 340, 110, 20);

        jLabel24.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel24.setForeground(new java.awt.Color(204, 204, 255));
        jLabel24.setText("°C / 10");
        jPanel1.add(jLabel24);
        jLabel24.setBounds(270, 250, 80, 20);

        Bat1TempField.setEditable(false);
        Bat1TempField.setBackground(new java.awt.Color(204, 204, 255));
        Bat1TempField.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        Bat1TempField.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        Bat1TempField.setText("WAITING...");
        Bat1TempField.setFocusable(false);
        jPanel1.add(Bat1TempField);
        Bat1TempField.setBounds(480, 180, 110, 20);

        jLabel26.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel26.setForeground(new java.awt.Color(204, 204, 255));
        jLabel26.setText("°C / 10");
        jPanel1.add(jLabel26);
        jLabel26.setBounds(600, 180, 80, 20);

        jLabel27.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel27.setForeground(new java.awt.Color(204, 204, 255));
        jLabel27.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel27.setText("Voltage:");
        jPanel1.add(jLabel27);
        jLabel27.setBounds(360, 240, 110, 20);

        bat1VoltageField.setEditable(false);
        bat1VoltageField.setBackground(new java.awt.Color(204, 204, 255));
        bat1VoltageField.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        bat1VoltageField.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        bat1VoltageField.setText("WAITING...");
        bat1VoltageField.setFocusable(false);
        jPanel1.add(bat1VoltageField);
        bat1VoltageField.setBounds(480, 240, 110, 20);

        jLabel28.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel28.setForeground(new java.awt.Color(204, 204, 255));
        jLabel28.setText("mV");
        jPanel1.add(jLabel28);
        jLabel28.setBounds(600, 240, 80, 20);

        jLabel29.setFont(new java.awt.Font("Lucida Grande", 1, 26)); // NOI18N
        jLabel29.setForeground(new java.awt.Color(255, 255, 255));
        jLabel29.setText("POD DATA");
        jPanel1.add(jLabel29);
        jLabel29.setBounds(10, 110, 170, 30);

        saveButton.setBackground(new java.awt.Color(204, 204, 255));
        saveButton.setText("SAVE TO FILE");
        saveButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                saveButtonActionPerformed(evt);
            }
        });
        jPanel1.add(saveButton);
        saveButton.setBounds(450, 490, 200, 29);

        settingsButton.setBackground(new java.awt.Color(204, 204, 255));
        settingsButton.setText("NETWORK SETTINGS...");
        settingsButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                settingsButtonActionPerformed(evt);
            }
        });
        jPanel1.add(settingsButton);
        settingsButton.setBounds(230, 490, 200, 29);

        masterField.setEditable(false);
        masterField.setBackground(new java.awt.Color(255, 51, 51));
        masterField.setFocusable(false);
        jPanel1.add(masterField);
        masterField.setBounds(370, 10, 60, 50);

        jLabel30.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel30.setForeground(new java.awt.Color(204, 204, 255));
        jLabel30.setText("cm s^-2");
        jPanel1.add(jLabel30);
        jLabel30.setBounds(270, 160, 80, 20);

        slave0Field.setEditable(false);
        slave0Field.setBackground(new java.awt.Color(255, 51, 51));
        slave0Field.setFocusable(false);
        jPanel1.add(slave0Field);
        slave0Field.setBounds(480, 10, 60, 50);

        jLabel31.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel31.setForeground(new java.awt.Color(204, 204, 255));
        jLabel31.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel31.setText("SLAVE 0");
        jPanel1.add(jLabel31);
        jLabel31.setBounds(470, 60, 80, 20);

        slave1Field.setEditable(false);
        slave1Field.setBackground(new java.awt.Color(255, 51, 51));
        slave1Field.setFocusable(false);
        jPanel1.add(slave1Field);
        slave1Field.setBounds(580, 10, 60, 50);

        jLabel32.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel32.setForeground(new java.awt.Color(204, 204, 255));
        jLabel32.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel32.setText("SLAVE 1");
        jPanel1.add(jLabel32);
        jLabel32.setBounds(570, 60, 80, 20);

        slave2Field.setEditable(false);
        slave2Field.setBackground(new java.awt.Color(255, 51, 51));
        slave2Field.setFocusable(false);
        jPanel1.add(slave2Field);
        slave2Field.setBounds(680, 10, 60, 50);

        jLabel33.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel33.setForeground(new java.awt.Color(204, 204, 255));
        jLabel33.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel33.setText("SLAVE 2");
        jPanel1.add(jLabel33);
        jLabel33.setBounds(670, 60, 80, 20);

        podField.setEditable(false);
        podField.setBackground(new java.awt.Color(204, 204, 255));
        podField.setFont(new java.awt.Font("Lucida Grande", 1, 24)); // NOI18N
        podField.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        podField.setFocusable(false);
        jPanel1.add(podField);
        podField.setBounds(890, 10, 60, 50);

        jLabel34.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel34.setForeground(new java.awt.Color(204, 204, 255));
        jLabel34.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel34.setText("STATUS");
        jLabel34.setFocusable(false);
        jPanel1.add(jLabel34);
        jLabel34.setBounds(890, 80, 60, 20);

        slave3Field.setEditable(false);
        slave3Field.setBackground(new java.awt.Color(255, 51, 51));
        slave3Field.setFocusable(false);
        jPanel1.add(slave3Field);
        slave3Field.setBounds(790, 10, 60, 50);

        jLabel35.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel35.setForeground(new java.awt.Color(204, 204, 255));
        jLabel35.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel35.setText("SLAVE 3");
        jPanel1.add(jLabel35);
        jLabel35.setBounds(780, 60, 80, 20);

        jLabel36.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel36.setForeground(new java.awt.Color(204, 204, 255));
        jLabel36.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel36.setText("POD");
        jLabel36.setFocusable(false);
        jPanel1.add(jLabel36);
        jLabel36.setBounds(900, 60, 40, 20);

        launchConsole.setBackground(new java.awt.Color(204, 204, 255));
        launchConsole.setText("LAUNCH CONSOLE");
        launchConsole.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                launchConsoleActionPerformed(evt);
            }
        });
        jPanel1.add(launchConsole);
        launchConsole.setBounds(10, 490, 200, 29);

        groundProximityField.setEditable(false);
        groundProximityField.setBackground(new java.awt.Color(204, 204, 255));
        groundProximityField.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        groundProximityField.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        groundProximityField.setText("WAITING...");
        groundProximityField.setFocusable(false);
        groundProximityField.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                groundProximityFieldActionPerformed(evt);
            }
        });
        jPanel1.add(groundProximityField);
        groundProximityField.setBounds(150, 370, 110, 20);

        jLabel37.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel37.setForeground(new java.awt.Color(204, 204, 255));
        jLabel37.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel37.setText("Stripe Count:");
        jPanel1.add(jLabel37);
        jLabel37.setBounds(-30, 340, 170, 20);

        jLabel3.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel3.setForeground(new java.awt.Color(204, 204, 255));
        jLabel3.setText("stripes");
        jPanel1.add(jLabel3);
        jLabel3.setBounds(270, 340, 80, 20);

        jLabel38.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel38.setForeground(new java.awt.Color(204, 204, 255));
        jLabel38.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel38.setText("Rail Proximity:");
        jPanel1.add(jLabel38);
        jLabel38.setBounds(-30, 400, 170, 20);

        railProximityField.setEditable(false);
        railProximityField.setBackground(new java.awt.Color(204, 204, 255));
        railProximityField.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        railProximityField.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        railProximityField.setText("WAITING...");
        railProximityField.setFocusable(false);
        railProximityField.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                railProximityFieldActionPerformed(evt);
            }
        });
        jPanel1.add(railProximityField);
        railProximityField.setBounds(150, 400, 110, 20);

        jLabel39.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel39.setForeground(new java.awt.Color(204, 204, 255));
        jLabel39.setText("mm");
        jPanel1.add(jLabel39);
        jLabel39.setBounds(270, 400, 80, 20);

        jLabel40.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel40.setForeground(new java.awt.Color(204, 204, 255));
        jLabel40.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel40.setText("Pusher Detected:");
        jPanel1.add(jLabel40);
        jLabel40.setBounds(-30, 430, 170, 20);

        pusherField.setEditable(false);
        pusherField.setBackground(new java.awt.Color(204, 204, 255));
        pusherField.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        pusherField.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        pusherField.setText("WAITING...");
        pusherField.setFocusable(false);
        pusherField.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                pusherFieldActionPerformed(evt);
            }
        });
        jPanel1.add(pusherField);
        pusherField.setBounds(150, 430, 110, 20);

        jLabel41.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel41.setForeground(new java.awt.Color(204, 204, 255));
        jLabel41.setText("Y/N");
        jPanel1.add(jLabel41);
        jLabel41.setBounds(270, 430, 80, 20);

        jLabel42.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel42.setForeground(new java.awt.Color(204, 204, 255));
        jLabel42.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel42.setText("Temperature:");
        jPanel1.add(jLabel42);
        jLabel42.setBounds(340, 180, 130, 20);

        jLabel43.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel43.setForeground(new java.awt.Color(255, 255, 255));
        jLabel43.setHorizontalAlignment(javax.swing.SwingConstants.LEFT);
        jLabel43.setText("ACCUMULATOR PRESSURES");
        jPanel1.add(jLabel43);
        jLabel43.setBounds(700, 180, 200, 20);

        jLabel44.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel44.setForeground(new java.awt.Color(255, 255, 255));
        jLabel44.setHorizontalAlignment(javax.swing.SwingConstants.LEFT);
        jLabel44.setText("BATTERY 2");
        jPanel1.add(jLabel44);
        jLabel44.setBounds(370, 270, 110, 20);

        jLabel45.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel45.setForeground(new java.awt.Color(204, 204, 255));
        jLabel45.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel45.setText("Temperature:");
        jPanel1.add(jLabel45);
        jLabel45.setBounds(370, 300, 100, 20);

        Bat2TempField.setEditable(false);
        Bat2TempField.setBackground(new java.awt.Color(204, 204, 255));
        Bat2TempField.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        Bat2TempField.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        Bat2TempField.setText("WAITING...");
        Bat2TempField.setFocusable(false);
        jPanel1.add(Bat2TempField);
        Bat2TempField.setBounds(480, 300, 110, 20);

        jLabel46.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel46.setForeground(new java.awt.Color(204, 204, 255));
        jLabel46.setText("°C / 10");
        jPanel1.add(jLabel46);
        jLabel46.setBounds(600, 300, 80, 20);

        jLabel25.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel25.setForeground(new java.awt.Color(204, 204, 255));
        jLabel25.setText("mA");
        jPanel1.add(jLabel25);
        jLabel25.setBounds(600, 330, 80, 20);

        bat2CurrentField.setEditable(false);
        bat2CurrentField.setBackground(new java.awt.Color(204, 204, 255));
        bat2CurrentField.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        bat2CurrentField.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        bat2CurrentField.setText("WAITING...");
        bat2CurrentField.setFocusable(false);
        jPanel1.add(bat2CurrentField);
        bat2CurrentField.setBounds(480, 330, 110, 20);

        jLabel47.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel47.setForeground(new java.awt.Color(204, 204, 255));
        jLabel47.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel47.setText("Current:");
        jPanel1.add(jLabel47);
        jLabel47.setBounds(360, 330, 110, 20);

        jLabel48.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel48.setForeground(new java.awt.Color(204, 204, 255));
        jLabel48.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel48.setText("Voltage:");
        jPanel1.add(jLabel48);
        jLabel48.setBounds(360, 360, 110, 20);

        bat2VoltageField.setEditable(false);
        bat2VoltageField.setBackground(new java.awt.Color(204, 204, 255));
        bat2VoltageField.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        bat2VoltageField.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        bat2VoltageField.setText("WAITING...");
        bat2VoltageField.setFocusable(false);
        jPanel1.add(bat2VoltageField);
        bat2VoltageField.setBounds(480, 360, 110, 20);

        jLabel49.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel49.setForeground(new java.awt.Color(204, 204, 255));
        jLabel49.setText("mV");
        jPanel1.add(jLabel49);
        jLabel49.setBounds(600, 360, 80, 20);

        jLabel50.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel50.setForeground(new java.awt.Color(255, 255, 255));
        jLabel50.setHorizontalAlignment(javax.swing.SwingConstants.LEFT);
        jLabel50.setText("BATTERY 3");
        jPanel1.add(jLabel50);
        jLabel50.setBounds(370, 390, 110, 20);

        jLabel51.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel51.setForeground(new java.awt.Color(204, 204, 255));
        jLabel51.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel51.setText("Temperature:");
        jPanel1.add(jLabel51);
        jLabel51.setBounds(370, 420, 100, 20);

        Bat3TempField.setEditable(false);
        Bat3TempField.setBackground(new java.awt.Color(204, 204, 255));
        Bat3TempField.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        Bat3TempField.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        Bat3TempField.setText("WAITING...");
        Bat3TempField.setFocusable(false);
        jPanel1.add(Bat3TempField);
        Bat3TempField.setBounds(480, 420, 110, 20);

        jLabel52.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel52.setForeground(new java.awt.Color(204, 204, 255));
        jLabel52.setText("°C / 10");
        jPanel1.add(jLabel52);
        jLabel52.setBounds(600, 420, 80, 20);

        jLabel53.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel53.setForeground(new java.awt.Color(204, 204, 255));
        jLabel53.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel53.setText("Voltage:");
        jPanel1.add(jLabel53);
        jLabel53.setBounds(360, 450, 110, 20);

        bat3VoltageField.setEditable(false);
        bat3VoltageField.setBackground(new java.awt.Color(204, 204, 255));
        bat3VoltageField.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        bat3VoltageField.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        bat3VoltageField.setText("WAITING...");
        bat3VoltageField.setFocusable(false);
        jPanel1.add(bat3VoltageField);
        bat3VoltageField.setBounds(480, 450, 110, 20);

        jLabel54.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel54.setForeground(new java.awt.Color(204, 204, 255));
        jLabel54.setText("mV");
        jPanel1.add(jLabel54);
        jLabel54.setBounds(600, 450, 80, 20);

        jLabel55.setFont(new java.awt.Font("Lucida Grande", 1, 26)); // NOI18N
        jLabel55.setForeground(new java.awt.Color(255, 255, 255));
        jLabel55.setText("TRACK DATA");
        jPanel1.add(jLabel55);
        jLabel55.setBounds(10, 290, 220, 30);

        jLabel56.setFont(new java.awt.Font("Lucida Grande", 1, 26)); // NOI18N
        jLabel56.setForeground(new java.awt.Color(255, 255, 255));
        jLabel56.setText("BATTERY DATA");
        jPanel1.add(jLabel56);
        jLabel56.setBounds(370, 110, 260, 30);

        readyButton.setBackground(new java.awt.Color(0, 153, 51));
        readyButton.setFont(new java.awt.Font("Lucida Grande", 1, 13)); // NOI18N
        readyButton.setForeground(new java.awt.Color(255, 255, 255));
        readyButton.setText("R E A D Y  T O  L A U N C H");
        readyButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                readyButtonActionPerformed(evt);
            }
        });
        jPanel1.add(readyButton);
        readyButton.setBounds(700, 490, 250, 29);

        jLabel57.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel57.setForeground(new java.awt.Color(255, 255, 255));
        jLabel57.setHorizontalAlignment(javax.swing.SwingConstants.LEFT);
        jLabel57.setText("BATTERY 1");
        jPanel1.add(jLabel57);
        jLabel57.setBounds(370, 150, 110, 20);

        jLabel58.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel58.setForeground(new java.awt.Color(204, 204, 255));
        jLabel58.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel58.setText("Accumulator 1:");
        jPanel1.add(jLabel58);
        jLabel58.setBounds(680, 210, 130, 20);

        accum1Field.setEditable(false);
        accum1Field.setBackground(new java.awt.Color(204, 204, 255));
        accum1Field.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        accum1Field.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        accum1Field.setText("WAITING...");
        accum1Field.setFocusable(false);
        jPanel1.add(accum1Field);
        accum1Field.setBounds(820, 210, 130, 20);

        jLabel60.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel60.setForeground(new java.awt.Color(204, 204, 255));
        jLabel60.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel60.setText("Accumulator 2:");
        jPanel1.add(jLabel60);
        jLabel60.setBounds(680, 240, 130, 20);

        accum2Field.setEditable(false);
        accum2Field.setBackground(new java.awt.Color(204, 204, 255));
        accum2Field.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        accum2Field.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        accum2Field.setText("WAITING...");
        accum2Field.setFocusable(false);
        jPanel1.add(accum2Field);
        accum2Field.setBounds(820, 240, 130, 20);

        jLabel61.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel61.setForeground(new java.awt.Color(204, 204, 255));
        jLabel61.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel61.setText("Accumulator 3:");
        jPanel1.add(jLabel61);
        jLabel61.setBounds(680, 270, 130, 20);

        accum3Field.setEditable(false);
        accum3Field.setBackground(new java.awt.Color(204, 204, 255));
        accum3Field.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        accum3Field.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        accum3Field.setText("WAITING...");
        accum3Field.setFocusable(false);
        jPanel1.add(accum3Field);
        accum3Field.setBounds(820, 270, 130, 20);

        jLabel62.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel62.setForeground(new java.awt.Color(204, 204, 255));
        jLabel62.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel62.setText("Accumulator 4:");
        jPanel1.add(jLabel62);
        jLabel62.setBounds(680, 300, 130, 20);

        accum4Field.setEditable(false);
        accum4Field.setBackground(new java.awt.Color(204, 204, 255));
        accum4Field.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        accum4Field.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        accum4Field.setText("WAITING...");
        accum4Field.setFocusable(false);
        jPanel1.add(accum4Field);
        accum4Field.setBounds(820, 300, 130, 20);

        brakeButton.setBackground(new java.awt.Color(255, 0, 0));
        brakeButton.setFont(new java.awt.Font("Lucida Grande", 1, 13)); // NOI18N
        brakeButton.setForeground(new java.awt.Color(255, 255, 255));
        brakeButton.setText("B R A K E");
        brakeButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                brakeButtonActionPerformed(evt);
            }
        });
        jPanel1.add(brakeButton);
        brakeButton.setBounds(700, 390, 250, 29);

        killPowerButton1.setBackground(new java.awt.Color(255, 0, 0));
        killPowerButton1.setFont(new java.awt.Font("Lucida Grande", 1, 13)); // NOI18N
        killPowerButton1.setForeground(new java.awt.Color(255, 255, 255));
        killPowerButton1.setText("K I L L  P O W E R");
        killPowerButton1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                killPowerButton1ActionPerformed(evt);
            }
        });
        jPanel1.add(killPowerButton1);
        killPowerButton1.setBounds(700, 440, 250, 29);

        jLabel59.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel59.setForeground(new java.awt.Color(204, 204, 255));
        jLabel59.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel59.setText("State:");
        jPanel1.add(jLabel59);
        jLabel59.setBounds(680, 150, 130, 20);

        hydraulicStateField.setEditable(false);
        hydraulicStateField.setBackground(new java.awt.Color(204, 204, 255));
        hydraulicStateField.setFont(new java.awt.Font("Lucida Grande", 1, 16)); // NOI18N
        hydraulicStateField.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        hydraulicStateField.setText("WAITING...");
        hydraulicStateField.setFocusable(false);
        jPanel1.add(hydraulicStateField);
        hydraulicStateField.setBounds(820, 150, 130, 20);

        getContentPane().add(jPanel1);

        jLabel1.setIcon(new javax.swing.ImageIcon(getClass().getResource("/Background.png"))); // NOI18N
        getContentPane().add(jLabel1);

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void saveButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_saveButtonActionPerformed

        String desktop = System.getProperty ("user.home") + "/Desktop/";
        FileIOClass fileObj = new FileIOClass();
        fileObj.setCreatePath(desktop + this.getCurrentTimeStamp() + ".txt");
        //fileObj.writeFile(console.getText().split("\n"));
        fileObj.writeFile(consoleWindow.getText().split("\n"));
        this.printToConsole("CONSOLE LOG SAVED TO DESKTOP");
        JOptionPane.showMessageDialog(null, "\nConsole Saved to File.");
    }//GEN-LAST:event_saveButtonActionPerformed

    private void launchConsoleActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_launchConsoleActionPerformed
        consoleWindow.setVisible(true);
    }//GEN-LAST:event_launchConsoleActionPerformed

    private void groundProximityFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_groundProximityFieldActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_groundProximityFieldActionPerformed

    private void railProximityFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_railProximityFieldActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_railProximityFieldActionPerformed

    private void pusherFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_pusherFieldActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_pusherFieldActionPerformed

    private void readyButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_readyButtonActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_readyButtonActionPerformed

    private void brakeButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_brakeButtonActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_brakeButtonActionPerformed

    private void killPowerButton1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_killPowerButton1ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_killPowerButton1ActionPerformed

    private void settingsButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_settingsButtonActionPerformed
        
        settingsWindow.setVisible(true);
        
    }//GEN-LAST:event_settingsButtonActionPerformed

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
                new GUI(/*parentPointer*/).setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JTextField Bat1TempField;
    private javax.swing.JTextField Bat2TempField;
    private javax.swing.JTextField Bat3TempField;
    private javax.swing.JTextField accelField;
    private javax.swing.JTextField accelField1;
    private javax.swing.JTextField accum1Field;
    private javax.swing.JTextField accum2Field;
    private javax.swing.JTextField accum3Field;
    private javax.swing.JTextField accum4Field;
    private javax.swing.JTextField bat1CurrentField;
    private javax.swing.JTextField bat1VoltageField;
    private javax.swing.JTextField bat2CurrentField;
    private javax.swing.JTextField bat2VoltageField;
    private javax.swing.JTextField bat3VoltageField;
    private javax.swing.JButton brakeButton;
    private javax.swing.JTextField groundProximityField;
    private javax.swing.JTextField hydraulicStateField;
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
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel30;
    private javax.swing.JLabel jLabel31;
    private javax.swing.JLabel jLabel32;
    private javax.swing.JLabel jLabel33;
    private javax.swing.JLabel jLabel34;
    private javax.swing.JLabel jLabel35;
    private javax.swing.JLabel jLabel36;
    private javax.swing.JLabel jLabel37;
    private javax.swing.JLabel jLabel38;
    private javax.swing.JLabel jLabel39;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel40;
    private javax.swing.JLabel jLabel41;
    private javax.swing.JLabel jLabel42;
    private javax.swing.JLabel jLabel43;
    private javax.swing.JLabel jLabel44;
    private javax.swing.JLabel jLabel45;
    private javax.swing.JLabel jLabel46;
    private javax.swing.JLabel jLabel47;
    private javax.swing.JLabel jLabel48;
    private javax.swing.JLabel jLabel49;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JLabel jLabel50;
    private javax.swing.JLabel jLabel51;
    private javax.swing.JLabel jLabel52;
    private javax.swing.JLabel jLabel53;
    private javax.swing.JLabel jLabel54;
    private javax.swing.JLabel jLabel55;
    private javax.swing.JLabel jLabel56;
    private javax.swing.JLabel jLabel57;
    private javax.swing.JLabel jLabel58;
    private javax.swing.JLabel jLabel59;
    private javax.swing.JLabel jLabel6;
    private javax.swing.JLabel jLabel60;
    private javax.swing.JLabel jLabel61;
    private javax.swing.JLabel jLabel62;
    private javax.swing.JLabel jLabel7;
    private javax.swing.JLabel jLabel8;
    private javax.swing.JLabel jLabel9;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel2;
    private javax.swing.JButton killPowerButton1;
    private javax.swing.JButton launchConsole;
    private javax.swing.JTextField masterField;
    private javax.swing.JTextField podField;
    private javax.swing.JTextField positionField;
    private javax.swing.JTextField positionField1;
    private javax.swing.JTextField pusherField;
    private javax.swing.JTextField railProximityField;
    private javax.swing.JButton readyButton;
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
    // End of variables declaration//GEN-END:variables
}
