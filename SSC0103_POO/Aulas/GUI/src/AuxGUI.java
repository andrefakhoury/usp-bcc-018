import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class AuxGUI extends JFrame implements ActionListener {

    private JButton btnOk;
    private JLabel lblTest;

    @Override
    public void actionPerformed(ActionEvent actionEvent) {
        if (actionEvent.getActionCommand().equals("a")) {
            if (lblTest.getText().equals("abacaba"))
                lblTest.setText("teste");
            else
                lblTest.setText("abacaba");
        }
    }

    public AuxGUI() {
        super("Titulo");

        this.setSize(1000, 1000);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setLayout(new GridLayout());

        JPanel jPanel = new JPanel();
        jPanel.setLayout(new FlowLayout());

        this.add(jPanel);

        lblTest = new JLabel("teste");
        jPanel.add(lblTest);

        btnOk = new JButton("OK");
        btnOk.addActionListener(this);

        jPanel.add(btnOk);

        JMenu jMenu = new JMenu("AAAAAAAAAAAA");
        JMenuItem jItem = new JMenuItem("teste");
        jMenu.add(jItem);


        jPanel.add(jMenu);

        this.setVisible(true);
    }
}