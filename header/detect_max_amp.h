
//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i

static unsigned char max = 0;
static unsigned char tempA;
/* complete the state machine. */

void Detect_Max_Amp()
{
    tempA = ~PINA & 0xF8;
    switch(detect_max_amp_state)
    {
        case DMAInit: detect_max_amp_state = DMA_Wait;
            break;
	case DMA_Wait: detect_max_amp_state =  (tempA > max) ? DMA_Ch : DMA_Wait; break;
	case DMA_Ch: detect_max_amp_state = DMA_Wait; break;
        default:
            break;
    }
    switch(detect_max_amp_state)
    {
        case DMAInit:
            break;
	case DMA_Wait: PORTB |= max; break;
	case DMA_Ch: PORTB &= 0x07; max = tempA; break;
        default:
            break;
    }
}
