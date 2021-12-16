using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace RTTTL_Converter
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            String tempoString = textBox2.Text;
            float tempo = 0;
            try
            {
                tempo = Int16.Parse(tempoString);
            }
            catch(Exception)
            {
                MessageBox.Show("Tempo incottect number: \"" + tempoString + "\".");
                return;
            }
            if (tempo < 40 || tempo > 500)
            {
                MessageBox.Show("Tempo \"" + tempo + "\" is not in correct range.");
                return;
            }

            String text = textBox1.Text;
            text = text.Replace("\n", " ");
            text = text.Replace("\r", " ");
            text = text.Replace(",", " ");
            text = text.Replace(";", " ");
            text = text.Replace("  ", " ");
            text = text.Replace("  ", " ");
            text = text.Replace("  ", " ");
            text = text.Replace("  ", " ");
            text = text.Trim();
            String[] notes = text.Split(' ');
            String result = "//tempo: " + tempo + "\n\n";
            String result2 = "static const byte melody PROGMEM = {\n";
            foreach (String note in notes)
            {

                bool x2 = note.Contains('.');
                String noteString = note.Replace(".", "").Trim();
                String toneString = GetNotNumbers(noteString);
                if (toneString.Equals(""))
                {
                    MessageBox.Show("No note at \"" + note + "\".");
                    return;
                }
                String durationString = "";
                String octaveString = "";
                String[] durAndOct = noteString.Split(toneString);
                if (durAndOct.Length > 1)
                {
                    durationString = durAndOct[0];
                    octaveString = durAndOct[1];
                }
                toneString = toneString.ToLower();
                durationString = durationString.ToLower();
                octaveString = octaveString.ToLower();

                if (durationString.Equals(""))
                {
                    MessageBox.Show("Incorrent diration at \"" + note + "\".");
                    return;
                }
                String noteAndOctaveString = toneString + octaveString;
                int noteNumber = -1;

                if (noteAndOctaveString.Equals("c1")) noteNumber = 0;
                if (noteAndOctaveString.Equals("#c1")) noteNumber = 1;
                if (noteAndOctaveString.Equals("d1")) noteNumber = 2;
                if (noteAndOctaveString.Equals("#d1")) noteNumber = 3;
                if (noteAndOctaveString.Equals("e1")) noteNumber = 4;
                if (noteAndOctaveString.Equals("f1")) noteNumber = 5;
                if (noteAndOctaveString.Equals("#f1")) noteNumber = 6;
                if (noteAndOctaveString.Equals("g1")) noteNumber = 7;
                if (noteAndOctaveString.Equals("#g1")) noteNumber = 8;
                if (noteAndOctaveString.Equals("a1")) noteNumber = 9;
                if (noteAndOctaveString.Equals("#a1")) noteNumber = 10;
                if (noteAndOctaveString.Equals("b1")) noteNumber = 11;

                if (noteAndOctaveString.Equals("c2")) noteNumber = 12;
                if (noteAndOctaveString.Equals("#c2")) noteNumber = 13;
                if (noteAndOctaveString.Equals("d2")) noteNumber = 14;
                if (noteAndOctaveString.Equals("#d2")) noteNumber = 15;
                if (noteAndOctaveString.Equals("e2")) noteNumber = 16;
                if (noteAndOctaveString.Equals("f2")) noteNumber = 17;
                if (noteAndOctaveString.Equals("#f2")) noteNumber = 18;
                if (noteAndOctaveString.Equals("g2")) noteNumber = 19;
                if (noteAndOctaveString.Equals("#g2")) noteNumber = 20;
                if (noteAndOctaveString.Equals("a2")) noteNumber = 21;
                if (noteAndOctaveString.Equals("#a2")) noteNumber = 22;
                if (noteAndOctaveString.Equals("b2")) noteNumber = 23;

                if (noteAndOctaveString.Equals("c3")) noteNumber = 24;
                if (noteAndOctaveString.Equals("#c3")) noteNumber = 25;
                if (noteAndOctaveString.Equals("d3")) noteNumber = 26;
                if (noteAndOctaveString.Equals("#d3")) noteNumber = 27;
                if (noteAndOctaveString.Equals("e3")) noteNumber = 28;
                if (noteAndOctaveString.Equals("f3")) noteNumber = 29;
                if (noteAndOctaveString.Equals("#f3")) noteNumber = 30;
                if (noteAndOctaveString.Equals("g3")) noteNumber = 31;
                if (noteAndOctaveString.Equals("#g3")) noteNumber = 32;
                if (noteAndOctaveString.Equals("a3")) noteNumber = 33;
                if (noteAndOctaveString.Equals("#a3")) noteNumber = 34;
                if (noteAndOctaveString.Equals("b3")) noteNumber = 35;

                if (toneString.Equals("-")) noteNumber = 36;

                if (noteNumber == -1)
                {
                    MessageBox.Show("Incorrent note at \"" + note + "\".");
                    return;
                }


                float duration = 0;
                try
                {
                    duration = Int32.Parse(durationString);
                    if (x2) 
                        duration = duration / 2;
                }
                catch (Exception exs)
                {
                    MessageBox.Show("Duration incorrect number at: \"" + note + "\".");
                    return;
                }
                float whole_notes_per_second = tempo / 240;
                float timeMs = 1000 / (whole_notes_per_second * duration);

                // Note frequency is calculated as (F*2^(n/12)),
                // Where n is note index, and F is the frequency of n=0
                // We can use C2=65.41, or C3=130.81. C2 is a bit shorter.
                double frequency = 260d * Math.Pow(2d, (noteNumber / 12d));

                //duration is float 2, 4, 8, 16, 32, 64
                String durationBinary = "";
                int duplicateNote = 1;
                if (duration == 2)
                {
                    durationBinary = "00"; //maybe duplicate note?
                    duplicateNote = 2;
                }
                else if (duration == 4) durationBinary = "00";
                else if (duration == 8) durationBinary = "01";
                else if (duration == 16) durationBinary = "10";
                else if (duration == 32) durationBinary = "11";
                else
                {
                    MessageBox.Show("Unsupported duration at: \"" + note + "\".");
                    return;
                }

                //noteNumber is what we need to store
                String noteBinary = Convert.ToString(noteNumber, 2);
                while (noteBinary.Length < 6) noteBinary = "0" + noteBinary;


                for (int dn = 0; dn < duplicateNote; dn++)
                {
                    result += "//Note: " + note;
                    result += ", tonS: " + toneString;
                    result += ", durS: " + durationString;
                    result += ", octS: " + octaveString;
                    result += ", nAoS: " + noteAndOctaveString;
                    result += "\n";
                    result += "//NoteNumber: " + noteNumber;
                    result += ", timeMs: " + timeMs;
                    result += ", frq: " + frequency;
                    result += "\n";
                    result += "//noteData: [" + durationBinary + noteBinary + "]";
                    result += "\n";
                    
                    result2 += "    0b" + durationBinary + noteBinary + ",\n";

                    if (noteNumber < 36)
                    {
                        result += "tone(pinBuzzer, " + (int)frequency + ");\n";
                        result += "delay(" + (int)timeMs + ");\n";
                        result += "noTone(pinBuzzer);\n";
                        result += "delay(10);\n\n";
                    }
                    else
                    {
                        result += "delay(" + (int)timeMs + ");\n\n";
                    }
                }
            }
            result2 += "};";
            richTextBox1.Text = result;
            richTextBox2.Text = result2;
        }

        private string GetNotNumbers(string input)
        {
            return new string(input.Where(c => !char.IsDigit(c)).ToArray());
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void richTextBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            richTextBox1.Text = "";
        }

        private void button5_Click(object sender, EventArgs e)
        {
            richTextBox2.Text = "";
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Clipboard.SetText(richTextBox1.Text);
            richTextBox1.SelectAll();
            richTextBox1.Focus();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Clipboard.SetText(richTextBox2.Text);
            richTextBox2.SelectAll();
            richTextBox2.Focus();
        }
    }
}
