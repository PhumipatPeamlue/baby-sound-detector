import usb
from practicum import find_mcu_boards, McuBoard, PeriBoard
from time import sleep
import requests
url = 'https://notify-api.line.me/api/notify'
token = 'hUxzq01OsLqxITdLxpjhLOOw8yfl2lDS4tauNuaUlnU'
headers = {'content-type':'application/x-www-form-urlencoded','Authorization':'Bearer '+token}

devs = find_mcu_boards()

if len(devs) == 0:
    print("*** No practicum board found.")
    exit(1)

mcu = McuBoard(devs[0])
print("*** Practicum board found")
print("*** Manufacturer: %s" % \
		mcu.handle.getString(mcu.device.iManufacturer, 256))
print("*** Product: %s" % \
		mcu.handle.getString(mcu.device.iProduct, 256))
peri = PeriBoard(mcu)

count = 0
while True:
    try:
        sound = peri.get_sound()
        st = peri.get_detect_sound()

        if st is True:
            state = "DE"
            requests.post(url, headers=headers, data = {'message': 'Your baby is crying. Please check!'})
        else:
            state = "UN"

        print("Sound value: %d | state: %-8s " % (sound, state))
        sleep(0.5)


    except usb.core.USBError:
        print("USB error detected")
