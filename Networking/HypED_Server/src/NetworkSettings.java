
import javax.swing.UIManager;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Jack_Gargan
 */
public class NetworkSettings extends javax.swing.JFrame {

    
    private int _defaultBasePort = 5695, _basePort = 5695,
                _defaultSpaceXPort = 3000, _spaceXPort = 3000;
    private String _defaultSpaceXIP = "192.168.0.1", _spaceXIP = "192.168.0.1";
    
    /**
     * Creates new form GUI
     */
    public NetworkSettings() {
        try
        {
        UIManager.setLookAndFeel(
            UIManager.getCrossPlatformLookAndFeelClassName());
        } catch(Exception e){}
        
        initComponents();
        setLocationRelativeTo(null);
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
        basePortField = new javax.swing.JTextField();
        IPField = new javax.swing.JTextField();
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
        spaceXPortField = new javax.swing.JTextField();
        okButton = new javax.swing.JButton();
        defaultButton = new javax.swing.JButton();
        jLabel30 = new javax.swing.JLabel();
        jLabel7 = new javax.swing.JLabel();
        jLabel8 = new javax.swing.JLabel();
        jLabel9 = new javax.swing.JLabel();
        cancelButton = new javax.swing.JButton();
        jLabel1 = new javax.swing.JLabel();

        setTitle("Poddy McPodface – Network Settings");
        setBackground(new java.awt.Color(0, 0, 153));
        setForeground(new java.awt.Color(51, 0, 102));
        setResizable(false);
        setSize(new java.awt.Dimension(29, 16));
        getContentPane().setLayout(new org.netbeans.lib.awtextra.AbsoluteLayout());

        jPanel1.setOpaque(false);
        jPanel1.setLayout(null);

        basePortField.setBackground(new java.awt.Color(204, 204, 255));
        basePortField.setFont(new java.awt.Font("Lucida Grande", 2, 14)); // NOI18N
        basePortField.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        basePortField.setText("Enter port no. here...");
        basePortField.setFocusCycleRoot(true);
        jPanel1.add(basePortField);
        basePortField.setBounds(220, 70, 170, 20);

        IPField.setBackground(new java.awt.Color(204, 204, 255));
        IPField.setFont(new java.awt.Font("Lucida Grande", 2, 14)); // NOI18N
        IPField.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        IPField.setText("Enter IP here...");
        IPField.setFocusCycleRoot(true);
        IPField.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                IPFieldActionPerformed(evt);
            }
        });
        jPanel1.add(IPField);
        IPField.setBounds(220, 100, 170, 20);

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

        spaceXPortField.setBackground(new java.awt.Color(204, 204, 255));
        spaceXPortField.setFont(new java.awt.Font("Lucida Grande", 2, 14)); // NOI18N
        spaceXPortField.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        spaceXPortField.setText("Enter port no. here...");
        spaceXPortField.setFocusCycleRoot(true);
        jPanel1.add(spaceXPortField);
        spaceXPortField.setBounds(220, 130, 170, 20);

        okButton.setBackground(new java.awt.Color(204, 204, 255));
        okButton.setText("OK");
        okButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                okButtonActionPerformed(evt);
            }
        });
        jPanel1.add(okButton);
        okButton.setBounds(280, 170, 110, 29);

        defaultButton.setBackground(new java.awt.Color(204, 204, 255));
        defaultButton.setText("DEFAULT");
        defaultButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                defaultButtonActionPerformed(evt);
            }
        });
        jPanel1.add(defaultButton);
        defaultButton.setBounds(10, 170, 110, 29);

        jLabel30.setFont(new java.awt.Font("Lucida Grande", 1, 26)); // NOI18N
        jLabel30.setForeground(new java.awt.Color(255, 255, 255));
        jLabel30.setText("NETWORK SETTINGS");
        jPanel1.add(jLabel30);
        jLabel30.setBounds(10, 10, 310, 30);

        jLabel7.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel7.setForeground(new java.awt.Color(204, 204, 255));
        jLabel7.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel7.setText("SpaceX IP Address:");
        jPanel1.add(jLabel7);
        jLabel7.setBounds(40, 100, 170, 20);

        jLabel8.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel8.setForeground(new java.awt.Color(204, 204, 255));
        jLabel8.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel8.setText("SpaceX Port Number:");
        jPanel1.add(jLabel8);
        jLabel8.setBounds(40, 130, 170, 20);

        jLabel9.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        jLabel9.setForeground(new java.awt.Color(204, 204, 255));
        jLabel9.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel9.setText("Base-Station Port Number:");
        jPanel1.add(jLabel9);
        jLabel9.setBounds(0, 70, 210, 20);

        cancelButton.setBackground(new java.awt.Color(204, 204, 255));
        cancelButton.setText("CANCEL");
        cancelButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                cancelButtonActionPerformed(evt);
            }
        });
        jPanel1.add(cancelButton);
        cancelButton.setBounds(160, 170, 110, 29);

        jLabel1.setIcon(new javax.swing.ImageIcon(getClass().getResource("/Background.png"))); // NOI18N
        jPanel1.add(jLabel1);
        jLabel1.setBounds(0, 0, 420, 210);

        getContentPane().add(jPanel1, new org.netbeans.lib.awtextra.AbsoluteConstraints(0, 0, 419, 207));

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void IPFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_IPFieldActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_IPFieldActionPerformed

    private void cancelButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_cancelButtonActionPerformed
        this.setVisible(false);
    }//GEN-LAST:event_cancelButtonActionPerformed

    private void defaultButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_defaultButtonActionPerformed
        _basePort = _defaultBasePort;
        _spaceXPort = _defaultSpaceXPort;
        _spaceXIP = _defaultSpaceXIP;
        
        basePortField.setText(Integer.toString(_basePort));
        IPField.setText(_spaceXIP);
        spaceXPortField.setText(Integer.toString(_spaceXPort));
    }//GEN-LAST:event_defaultButtonActionPerformed

    private void okButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_okButtonActionPerformed
        _basePort = Integer.parseInt(basePortField.getText());
        _spaceXPort = Integer.parseInt(spaceXPortField.getText());
        _spaceXIP = IPField.getText();
        
        this.setVisible(false);
    }//GEN-LAST:event_okButtonActionPerformed

    public int getSpaceXPort() { return _spaceXPort; }
    
    public int getBasePort() { return _basePort; }
    
    public String getSpaceXIP() { return _spaceXIP; }
    
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
                    javax.swing.UIManager.setLookAndFeel(javax.swing.UIManager.getCrossPlatformLookAndFeelClassName());
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
                new NetworkSettings().setVisible(true); // GUI
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JTextField IPField;
    private javax.swing.JTextField accelField1;
    private javax.swing.JTextField basePortField;
    private javax.swing.JButton cancelButton;
    private javax.swing.JButton defaultButton;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel10;
    private javax.swing.JLabel jLabel11;
    private javax.swing.JLabel jLabel12;
    private javax.swing.JLabel jLabel13;
    private javax.swing.JLabel jLabel14;
    private javax.swing.JLabel jLabel15;
    private javax.swing.JLabel jLabel16;
    private javax.swing.JLabel jLabel17;
    private javax.swing.JLabel jLabel30;
    private javax.swing.JLabel jLabel7;
    private javax.swing.JLabel jLabel8;
    private javax.swing.JLabel jLabel9;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel2;
    private javax.swing.JButton okButton;
    private javax.swing.JTextField positionField1;
    private javax.swing.JTextField spaceXPortField;
    private javax.swing.JTextField statusField1;
    private javax.swing.JTextField velocityField1;
    // End of variables declaration//GEN-END:variables
}
