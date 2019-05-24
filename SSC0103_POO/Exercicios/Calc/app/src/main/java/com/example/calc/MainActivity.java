package com.example.calc;

import android.content.Context;
import android.graphics.Color;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import org.w3c.dom.Text;

import java.time.Duration;

public class MainActivity extends AppCompatActivity {

    private int currentOp;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        currentOp = 1;

        FloatingActionButton fab = findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    public void btnNumberClick(View v) {
        EditText txtOp1 = findViewById(R.id.txtOp1);
        EditText txtOp2 = findViewById(R.id.txtOp2);

        Button btn = findViewById(v.getId());

        if (currentOp == 1) {
            txtOp1.append(btn.getText());
        } else {
            txtOp2.append(btn.getText());
        }
    }

    public void btnClear(View v) {
        EditText txt1 = findViewById(R.id.txtOp1);
        EditText txt2 = findViewById(R.id.txtOp2);
        EditText txtOp = findViewById(R.id.txtOperador);
        TextView txtAns = findViewById(R.id.txtAns);

        txt1.setText("");
        txt2.setText("");
        txtOp.setText("");
        txtAns.setText("");

        currentOp = 1;
        btnChangeOperando1(v);
    }

    public void btnOperation(View v) {
        EditText txtOp = findViewById(R.id.txtOperador);
        Button btn = findViewById(v.getId());

        txtOp.setText(btn.getText());
    }

    public void btnChangeOperando1(View v) {
        TextView txt1, txt2;
        txt1 = findViewById(R.id.txtOp1);
        txt2 = findViewById(R.id.txtOp2);

        txt1.setBackgroundColor(0xF49D9D);
        txt2.setBackgroundColor(0);

        currentOp = 1;
    }

    public void btnChangeOperando2(View v) {
        TextView txt1, txt2;
        txt1 = findViewById(R.id.txtOp1);
        txt2 = findViewById(R.id.txtOp2);

        txt1.setBackgroundColor(0);
        txt2.setBackgroundColor(0xF49D9D);

        currentOp = 2;
    }

    public void btnRet(View v) {
        currentOp = 3 - currentOp;

        TextView txt1, txt2;
        txt1 = findViewById(R.id.txtOp1);
        txt2 = findViewById(R.id.txtOp2);

        String operacao = ((TextView)(findViewById(R.id.txtOperador))).getText().toString();
        if (operacao.equals("")) {
            Toast.makeText(this, "Nao foi definido o operador!", Toast.LENGTH_SHORT).show();
            return;
        }

        if (!"".equals(txt1.getText().toString()) && !"".equals(txt2.getText().toString())) {
            TextView txtAns = findViewById(R.id.txtAns);

            int ans = 0;

            int op1 = Integer.parseInt(txt1.getText().toString());
            int op2 = Integer.parseInt(txt2.getText().toString());

            switch (operacao) {
                case "+":
                    ans = op1 + op2;
                    break;
                case "-":
                    ans = op1 - op2;
                    break;
                case "*":
                    ans = op1 * op2;
                    break;
                case "/":
                    if (op2 == 0) {
                        Toast.makeText(this, "Dividendo nao pode ser 0!", Toast.LENGTH_SHORT).show();
                    } else {
                        ans = op1 / op2;
                    }
            }

            txtAns.setText(ans);
        } else {
            Toast.makeText(this, "Os dois operandos devem estar nao vazios!", Toast.LENGTH_SHORT).show();
        }
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
