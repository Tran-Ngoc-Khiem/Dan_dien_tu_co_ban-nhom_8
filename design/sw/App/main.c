/* USER CODE BEGIN Header */
/**
  * @file           : main.c
  * @brief          : Main program body
  * @attention
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/


/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#include "main.h"

uint8_t mode = 1;  // 1: Choi nh?c, 2: Ghi am, 3: Ph t nh?c
uint8_t song = 1;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	HAL_Init();
    SystemClock_Config();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_TIM2_CLK_ENABLE();

    /* ===== C?U H NH PA1 PWM TIM2_CH2 ===== */
    GPIO_InitTypeDef gpio = {0};
    gpio.Pin   = GPIO_PIN_1;
    gpio.Mode  = GPIO_MODE_AF_PP;
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &gpio);
    /* ===== KH?I T?O TIMER PWM ===== */
    htim2.Instance = TIM2;
    htim2.Init.Prescaler     = 127;
    htim2.Init.CounterMode   = TIM_COUNTERMODE_UP;
    htim2.Init.Period        = 20;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&htim2);

    TIM_OC_InitTypeDef sConfigOC = {0};
    sConfigOC.OCMode     = TIM_OCMODE_PWM1;
    sConfigOC.Pulse      = 0; // 50%
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2);

    PWM_SetFrequency(0); // ban d?u t?t ti?ng
HAL_Init();
 MX_GPIO_Init();
	  LCD_Clear();
	  LCD_Display();

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
HAL_Init();
 SystemClock_Config();
 MX_GPIO_Init();
  LCD_Init();
  LCD_Clear();
  LCD_Display();
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_I2C2_Init();
  /* USER CODE BEGIN 2 */
/* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

/* USER CODE BEGIN 3 */

		
		
				
				
				
		// Macro h? tr? ch?ng d?i phm (Debounce)
#define IS_BUTTON_PRESSED(PORT, PIN) (HAL_GPIO_ReadPin(PORT, PIN) == GPIO_PIN_RESET)

// --- X? l CC NT NH?N CHUNG (MODE/SONG/START-STOP) ---

// 1. Nt MODE (PB0) - Chuy?n ch? d?
if (IS_BUTTON_PRESSED(GPIOB, GPIO_PIN_0))
{
    HAL_Delay(50); // Ch?ng d?i phm
    if (IS_BUTTON_PRESSED(GPIOB, GPIO_PIN_0))
    {
        // T?t t?t c? cc tr?ng thi ?ang ch?i/ghi khi d?i ch? d?
        PWM_SetFrequency(0);
        isRecording = 0;
        isPlaying = 0;
        
        mode++;	
        if (mode > 3) mode = 1;
        LCD_Display();
        while (IS_BUTTON_PRESSED(GPIOB, GPIO_PIN_0)); // Ch? nh?c phm
    }
}

// 2. Nt SONG (PB1) - Ch?n Slot nh?c
if (IS_BUTTON_PRESSED(GPIOB, GPIO_PIN_1))
{
    HAL_Delay(50);
    if (IS_BUTTON_PRESSED(GPIOB, GPIO_PIN_1))
    {
        song++;
        if (song > 10) song = 1;
        LCD_Display();
        while (IS_BUTTON_PRESSED(GPIOB, GPIO_PIN_1));
    }
}

// 3. Nt START/STOP (PA3)
if (IS_BUTTON_PRESSED(GPIOA, GPIO_PIN_3))
{
    HAL_Delay(50);
    if (IS_BUTTON_PRESSED(GPIOA, GPIO_PIN_3))
    {
        switch (mode)
        {
            case 2: // CH? D? GHI AM
                if (isRecording)
                {
                    // D?ng Ghi m
                    isRecording = 0;
                    PWM_SetFrequency(0);
                    
                    // L?u d? li?u t? record_buf vo song_data c?a slot hi?n t?i
                    song_len[song] = record_len;
                    for (int i = 0; i < record_len; i++) {
                        song_data[song][i] = record_buf[i];
                    }
                    record_len = 0; // Reset buffer d? s? d?ng l?n sau
                    
                    // Thng bo l?u thnh cng v quay l?i hi?n th? chnh
                    LCD_Display();
                    LCD_GotoXY(1, 0);
                    LCD_Puts("Da luu!");
                    HAL_Delay(1000); // Hi?n th? 1 giy
                    LCD_Display();
                }
                else
                {
                    // B?t d?u Ghi m
                    isRecording = 1;
                    record_len = 0; // Xa d? li?u c? trong buffer
                    LCD_Display();
                }
                break;
                
            case 3: // CH? D? PHT NH?C
                // B?t/t?t pht nh?c (Toglle)
                isPlaying = !isPlaying;
                PWM_SetFrequency(0); // D?m b?o t?t ti?ng khi d?ng
                
                if (isPlaying) {
                    play_index = 0; // B?t d?u l?i t? d?u
                }
                
                LCD_Display();
                break;
        }
        while (IS_BUTTON_PRESSED(GPIOA, GPIO_PIN_3));
    }
}

// --- X? l LOGIC RI?NG C?A T?NG CH? D? ---
switch (mode)
{
case 1: // CH?I NH?C TR?C TI?P
    {
        // Ch? c?n pht n?t khi phm du?c nh?n
        uint32_t note = ReadNoteKey();
        if (note != 0)
        {
            PWM_SetFrequency(note);
            HAL_Delay(300); // Gi?m th?i gian gi? phm ?? ch?i linh ho?t h?n
        }
        else
        {
            PWM_SetFrequency(0); // T?t ti?ng khi nh?c phm
        }
        break;
    }

    case 2: // GHI AM
    {
        uint32_t note = ReadNoteKey();
        
        if (note != 0)
        {
            // V?a pht ra PA1
            PWM_SetFrequency(note);
            HAL_Delay(300); // Gi?m th?i gian gi? phm ?? ch?i linh ho?t h?n
            
            if (isRecording)
            {
                if (record_len < MAX_NOTES)
                {
                    // V?a l?u vo buffer
                    record_buf[record_len++] = note;
                    LCD_Display(); // C?p nh?t s? l?ng n?t
                }
                else
                {
                    // B? nh? d ??y, t? d?ng d?ng ghi m v l?u
                    // (T?i ?ay logic d l?p l?i t??ng t? nh? khi nh?n PA3 d? d?ng)
                    isRecording = 0;
                    song_len[song] = record_len;
                    for (int i = 0; i < record_len; i++) {
                        song_data[song][i] = record_buf[i];
                    }
                    record_len = 0;
                    
                    LCD_GotoXY(1, 0);
                    LCD_Puts("FULL. Da luu!");
                    HAL_Delay(1000);
                    LCD_Display();
                }
            }
        }
        else
        {
            PWM_SetFrequency(0);
        }
        break;
    }
    
    case 3: // PHT NH?C
    {
        // Logic pht l?p
        if (isPlaying)
        {
            if (song_len[song] > 0)
            {
                uint16_t current_note = song_data[song][play_index];
                
                // Pht n?t
                PWM_SetFrequency(current_note);
                HAL_Delay(300); 
                
                PWM_SetFrequency(0); // Ngh? ng?n gi?a cc n?t (d? nghe r rng h?n)
                HAL_Delay(50);
                
                play_index++;
                
                // Pht l?p (quay l?i d?u bi)
                if (play_index >= song_len[song])
                {
                    play_index = 0;
                }
            }
            else
            {
                // Khng c d? li?u, d?ng pht
                isPlaying = 0;
                PWM_SetFrequency(0);
                LCD_GotoXY(1, 0);
                LCD_Puts("Slot trong!");
                HAL_Delay(1000);
                LCD_Display();
            }
        } 
        else // ? ch? d? ch? (isPlaying=0) - V?n cho php ch?i tr?c ti?p ?? ki?m tra
        {
            uint32_t note = ReadNoteKey();
            if (note != 0)
            {
                PWM_SetFrequency(note);
                HAL_Delay(300);
            }
            else
            {
PWM_SetFrequency(0);
            }
        }
        break;
    }
}
HAL_Delay(10); // D? m?t kho?ng ngh? ng?n cho ton b? vng l?p

        
}
  /* USER CODE END 3 */
}


#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
