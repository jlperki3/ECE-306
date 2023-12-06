//******************************************************************************
//
//  Description: This file contains the Function prototypes
//
//  Jim Carlson
//  Aug 2013
//  Built with TI Code Composer Studio 12.2.0
//******************************************************************************
// Functions
    extern char display_line[4][11];
    extern char *display[4];
    extern unsigned char display_mode;
    extern volatile unsigned char display_changed;
    extern volatile unsigned char update_display;
    extern volatile unsigned int update_display_count;
    extern volatile unsigned int Time_Sequence;
    extern volatile char one_time;
    extern unsigned int test_value;
    extern char chosen_direction;
    extern char change;

// Initialization
void Init_Conditions(void);

// Interrupts
void enable_interrupts(void);
__interrupt void Timer0_B0_ISR(void);
__interrupt void switch_interrupt(void);

// Analog to Digital Converter
void Init_ADC(void);
void adc_line(char line, char location);
void HEXtoBCD(int hex_value);
void HEXtoBCD_TIMER(int hex_value);
void adc_line_timer(char line, char location);

// Clocks
void Init_Clocks(void);

// LED Configurations
void Init_LEDs(void);
void IR_LED_control(char selection);
void Backlite_control(char selection);

// LCD
void Display_Process(void);
void Display_Update(char p_L1,char p_L2,char p_L3,char p_L4);
void enable_display_update(void);
void update_string(char *string_data, int string);
void Init_LCD(void);
void lcd_clear(void);
void lcd_putc(char c);
void lcd_puts(char *s);

void lcd_power_on(void);
void lcd_write_line1(void);
void lcd_write_line2(void);
//void lcd_draw_time_page(void);
//void lcd_power_off(void);
void lcd_enter_sleep(void);
void lcd_exit_sleep(void);
//void lcd_write(unsigned char c);
//void out_lcd(unsigned char c);

void Write_LCD_Ins(char instruction);
void Write_LCD_Data(char data);
void ClrDisplay(void);
void ClrDisplay_Buffer_0(void);
void ClrDisplay_Buffer_1(void);
void ClrDisplay_Buffer_2(void);
void ClrDisplay_Buffer_3(void);

void SetPostion(char pos);
void DisplayOnOff(char data);
void lcd_BIG_mid(void);
void lcd_BIG_bot(void);
void lcd_120(void);

void lcd_4line(void);
void lcd_out(char *s, char line, char position);
void lcd_rotate(char view);

//void lcd_write(char data, char command);
void lcd_write(unsigned char c);
void lcd_write_line1(void);
void lcd_write_line2(void);
void lcd_write_line3(void);

void lcd_command( char data);
void LCD_test(void);
void LCD_iot_meassage_print(int nema_index);

// Menu
void Menu_Process(void);

// Ports
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(char smclk);
void Init_Port4(void);
void Init_Port5(void);
void Init_Port6(void);

// SPI
void Init_SPI_B1(void);
void SPI_B1_write(char byte);
void spi_rs_data(void);
void spi_rs_command(void);
void spi_LCD_idle(void);
void spi_LCD_active(void);
void SPI_test(void);
void WriteIns(char instruction);
void WriteData(char data);

// Switches
void Init_Switches(void);
void switch_control(void);
void enable_switch_SW1(void);
void enable_switch_SW2(void);
void disable_switch_SW1(void);
void disable_switch_SW2(void);
void Switches_Process(void);
void Init_Switch(void);
void Switch_Process(void);
void Switch1_Process(void);
void Switch2_Process(void);
void menu_act(void);
void menu_select(void);

// Timers
void Init_Timers(void);
void Init_Timer_B0(void);
void Init_Timer_B1(void);
void Init_Timer_B2(void);
void Init_Timer_B3(void);

void usleep(unsigned int usec);
void usleep10(unsigned int usec);
void five_msec_sleep(unsigned int msec);
void measure_delay(void);
void out_control_words(void);

//Movement
void Forward_Move(void);
void Forward_Slow(void);
void Reverse_Move(void);
void Display_Clock(void);
void wait_case(void);
void pause_case(void);
void start_case(void);
void run_case(void);
void triangle_run_case(void);
void end_case(void);
void Motors_Off(void);
void Run_Forward(void);
void Change_State(void);
void Line_Up(void);
void Turn_Right(void);
void Turn_Left(void);
void Turn_In(void);
void Wait (void);

//Serial
void Init_Serial_UCA0(char speed);
void Init_Serial_UCA1(char speed);
void USCI_A0_transmit(void);
void USCI_A1_transmit(void);
void IOT_Process(void);
void print_IOT(unsigned int thisLine);
void print_USB(void);
void populate (void);

//IOT
void Configure_IOT (void);
void Send_2_IOT (char command[]);
void Parse_Command (void);
void IOT_Command (void);
void Count_Commands (void);

//DAC
void Init_DAC(void);
void Init_REF(void);

// Project 10
void Course_Timer(void);
void Process_State(void);
void Arch (void);
void Start_Course (void);
void Forward_Search (void);
void Turn_Right_IOT (void);
void Turn_Left_IOT (void);
