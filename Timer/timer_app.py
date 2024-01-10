import threading
from pynput import keyboard
from plyer import notification
import winsound
import sys

timer = None
timer_seconds = 0
alt_pressed = False  # флаг нажатия альт-клавиши

def set_timer(minutes):
    global timer, timer_seconds
    if timer and timer.is_alive():
        timer.cancel()

    timer_seconds = minutes * 60

    def notify():
        notification.notify(
            title='Таймер завершен',
            message=f'Время вышло! Таймер был установлен на {minutes} минут',
            app_name='Тайcмер'
        )
        winsound.MessageBeep(winsound.MB_ICONEXCLAMATION)

    timer = threading.Timer(timer_seconds, notify)
    timer.start()
    notification.notify(
        title='Таймер установлен',
        message=f'Таймер установлен на {minutes} минут',
        app_name='Таймер'
    )


def stop_timer():
    global timer
    if timer and timer.is_alive():
        timer.cancel()

def show_notification(title, message):
    notification.notify(
        title=title,
        message=message,
        app_name='Таймер'
    )

def on_press(key):
    global alt_pressed
    try:
        if key == keyboard.Key.alt_l:  # Проверяем нажатие левой alt
            alt_pressed = True
        elif alt_pressed and key.char in '12345789':
            minutes = int(key.char)
            set_timer(minutes)
        elif alt_pressed and key.char == '0':
            stop_timer()
    except AttributeError:
        pass


def on_release(key):
    global alt_pressed
    if key == keyboard.Key.alt_l:  # Сбрасываем флаг при отпускании клавиши
        alt_pressed = False
    if key == keyboard.Key.esc and alt_pressed:  # Завершаем программу при нажатии Alt + esc
        sys.exit()

def main():
    with keyboard.Listener(on_press=on_press, on_release=on_release) as listener:
        listener.join()

if __name__ == "__main__":
    main()
