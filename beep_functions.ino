void one_beep(int tb=300){
  /*
  tone(buzzer_pin, 4186,tb);
  */
  }

void three_beep(){
  /*
  one_beep();
  delay(30);
  one_beep();
  delay(30);
  one_beep();
  delay(30);
  */

}

void music(){
  /*
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
      
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
     }
    tone(buzzer_pin, melody[thisNote], noteDuration * 0.9);
    delay(noteDuration);
    noTone(buzzer_pin);
    
  }*/
}