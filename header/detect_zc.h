
//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i
static unsigned char opp[8] = {4,5,6,7,0,1,2,3}; //opposite
static unsigned char sampleNo = 0;
static unsigned char lastDir;
static unsigned char temp;

/*complete the state machine*/

void Detect_ZC()
{
    temp = ~PINA & 0x07;
    switch(detect_zc_state)
    {
        case DZCInit:
	    lastDir = temp;
	    detect_zc_state = DZC_Off;
            break;
	case DZC_Off:
	    if (opp[lastDir] == temp){
		sampleNo++;
		if (sampleNo >= 2){
			sampleNo = 0;
			detect_zc_state = DZC_On;
		}
		else
			detect_zc_state = DZC_Off;
	    }
	    else{
		sampleNo = 0;
		lastDir = temp;
		detect_zc_state = DZC_Off;
	    }
	    break;
	case DZC_On: detect_zc_state = DZC_Off; lastDir = temp; break;
        default:
            detect_zc_state = DZCInit;
            break;
    }
    switch(detect_zc_state)
    {
        case DZCInit:
            break;
	case DZC_Off: PORTB &= 0xFB; break;
	case DZC_On: PORTB |= 0x04; break;
        default:
            break;
    }
}
