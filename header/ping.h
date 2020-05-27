
//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i

static unsigned int i = 0;

/*complete the state machine*/

void Ping()
{
    switch(ping_state)
    {
        case PInit: ping_state = PI_On; break;
	case PI_On: ping_state = (i >= 1) ? PI_Off : PI_On; i++; break;
	case PI_Off:
		    if (i >= 1 && i <= 10){
			    ping_state = PI_Off;
			    i++;
		    }
		    else{
			ping_state = PI_On;
			i = 0;
		    }
		    break;
        default:
            ping_state = PInit;
            break;
    }
    switch(ping_state)
    {
        case PInit: break;
	case PI_On: PORTB |= 0x01; break;
	case PI_Off: PORTB &= 0xFE; break;
        default:
            break;
    }
}
