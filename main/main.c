/*
 * @Author: lmh 885288596@qq.com
 * @Date: 2023-04-28 21:50:05
 * @LastEditors: lmh 885288596@qq.com
 * @LastEditTime: 2023-05-13 19:56:19
 * @FilePath: /st7789/main/main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <stdio.h>
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"
#include "../components/user_dev/SPI/User_dev_spi.h"
#include "../components/user_dev/TOUCH/touch_iic.h"
#include "../components/user_mid/lcd.h"
#include "../components/lvgl/lvgl.h"
#include "../components/lvgl/lvgl_driver/lv_port_disp.h"
#include "../components/lvgl/demos/music/lv_demo_music.h"
#include "lv_demos.h"

static esp_timer_handle_t lvgl_timer_handle = NULL;

static IRAM_ATTR void lv_timer_cb(void *arg)
{
   lv_tick_inc(1);
}

static esp_timer_create_args_t lvgl_timer = {
    .callback = &lv_timer_cb,
    .arg = NULL,
    .name = "lvgl_timer",
    .dispatch_method = ESP_TIMER_TASK};

esp_err_t _lv_timer_create(void)
{
   esp_err_t err = esp_timer_create(&lvgl_timer, &lvgl_timer_handle);
   err = esp_timer_start_periodic(lvgl_timer_handle, 1000); // 1毫秒回调
   if (err != ESP_OK)
   {
      ESP_LOGE("main", "lvgl定时器创建成功\r\n");
   }
   return err;
}

LV_IMG_DECLARE(shuyue);

IRAM_ATTR void imgtask(void *arg)
{
   lv_obj_t *img_temp = lv_img_create(lv_scr_act());
   lv_obj_align(img_temp, LV_ALIGN_CENTER, 0, 0);
   lv_obj_set_scrollbar_mode(img_temp, LV_SCROLLBAR_MODE_ON);

   while (true)
   {
      lv_img_set_src(img_temp, &shuyue);
      vTaskDelay(pdMS_TO_TICKS(100));
   }
}

// void learntask(void *arg);
// static void img_event_cb(lv_event_t *e)
// {
//    lv_event_code_t code = lv_event_get_code(e);
//    lv_obj_t *sw = lv_event_get_target(e);
//    if (code == LV_EVENT_VALUE_CHANGED)
//    {
//       /*获取开关状态*/
//       if (lv_obj_has_state(sw, LV_STATE_CHECKED))
//       {
//          lv_obj_t *img_temp = lv_img_create(lv_scr_act());
//          lv_obj_align(img_temp, LV_ALIGN_CENTER, 0, 0);
//          lv_obj_set_scrollbar_mode(img_temp, LV_SCROLLBAR_MODE_ON);
//          lv_img_set_src(img_temp, &shuyue);
//       }
//       else
//       {
//          LCD_Clear(0xffff);
//       }
//    }
// }

// void learntask(void *arg)
// {
//    // static lv_style_t style_obj1,style_obj2;
//    // lv_style_init(&style_obj1);
//    // lv_style_init(&style_obj2);
//    // lv_obj_t *kuang1 = lv_obj_create(lv_scr_act()); // 创建一个框
//    // lv_obj_t *kuang2 = lv_obj_create(lv_scr_act()); // 创建一个框
//    // lv_obj_set_size(kuang1, 100, 50);
//    // lv_obj_set_pos(kuang1, 20, 50);
//    // lv_obj_set_size(kuang2, 100, 50);
//    // lv_obj_set_pos(kuang2, 150, 50);
//    // /*创建框内子类*/
//    // lv_obj_t *obj1 = lv_label_create(kuang1);
//    // lv_obj_t *obj2 = lv_label_create(kuang2);
//    // lv_obj_set_style_border_width(kuang1, 1, 0);
//    // lv_obj_set_style_border_width(kuang2, 1, 0);
//    // lv_label_set_text(obj1, "limenghui");
//    // lv_label_set_text(obj2, "qushuyue");
//    // /*居中*/
//    // lv_obj_align(obj1, LV_ALIGN_CENTER, 0, 0);
//    // lv_obj_align(obj2, LV_ALIGN_CENTER, 0, 0);

//    // lv_style_set_bg_color(&style_obj1,lv_color_hex(0x000000));
//    // lv_style_set_text_color(&style_obj1,lv_color_hex(0xffffff));

//    // lv_obj_add_event_cb(kuang1,img_event_cb,LV_EVENT_CLICKED,NULL);

//    /*按钮*/
//    // lv_obj_t *btn = lv_btn_create(lv_scr_act());
//    // lv_obj_set_size(btn,50,50);
//    // lv_obj_center(btn);
//    /*开关 switch*/

//    // lv_obj_t *sw = lv_switch_create(lv_scr_act());

//    // lv_obj_center(sw);
//    // lv_obj_clear_state(sw, LV_STATE_CHECKED);
//    // lv_obj_add_event_cb(sw, img_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

//    /*下拉列表*/
// lv_obj_t *dd = lv_dropdown_create(lv_scr_act());

// lv_dropdown_set_options(dd,"one\ntwo");
// lv_obj_center(dd);
   
//    while (true)
//    {
//       vTaskDelay(10 / portTICK_PERIOD_MS);
//       /* code */
//    }
// }

void app_main(void)
{

   lv_init();
   lv_port_disp_init();
   _lv_timer_create();
   touch_iic_init();
   // lv_obj_t *d_obj ;
   // d_obj = lv_scr_act();
   // lv_obj_t *lab = lv_label_create(d_obj);
   // lv_label_set_text(lab,"hello_lvgl");
   // lv_obj_center(lab);
    lv_demo_music();
   // lv_demo_stress();
   //  lv_demo_widgets();
    //  lv_demo_keypad_encoder();
   // xTaskCreatePinnedToCore(imgtask, "imgtask", 4096*2, NULL, 0, NULL, 1);
   //xTaskCreatePinnedToCore(learntask, "learntask", 4096 * 2, NULL, 0, NULL, 1);
   while (true)
   {
      vTaskDelay(10 / portTICK_PERIOD_MS);
      lv_task_handler();
   }
}
