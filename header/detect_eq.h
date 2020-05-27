//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i
static unsigned char temp;
static unsigned char b = 10;

/*complete the state machine*/

void Detect_EQ()
{
    temp = ~PINA & 0xF8;
    switch(detect_eq_state)
    {
        case DEQInit: detect_eq_state = DEQ_F; break;
	case DEQ_F: detect_eq_state = (temp  == 0) ? DEQ_F : DEQ_T; break;
	case DEQ_T: detect_eq_state = (temp  == 0) ? DEQ_F : DEQ_T; break;
        default:
            detect_eq_state = DEQInit;
            break;
    }
    switch(detect_eq_state)
    {
	    case DEQInit: break;
	    case DEQ_F: if (b <= 1) {PORTB &= 0xFD; eq_running = 0;} if (b > 0) {b--;} break;
	    case DEQ_T: PORTB |= 0x02; b = 10; eq_running = 1; break;
        default:
            break;
    }
}
