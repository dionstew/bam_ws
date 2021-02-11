import cv2
import time
import datetime as dt
# import data_io

# load dataset
ayam_cascade = cv2.CascadeClassifier('warna-warni4-cascade.xml')

# To capture frame
image = cv2.VideoCapture(0)

def waktu():
    jam = dt.datetime.now().hour
    menit = dt.datetime.now().minute
    waktu = [jam, menit]
    return waktu

def detection():
    # read frame
    _, frame = image.read()
    
    # flip image
    frame = cv2.flip(frame, +1)
    
    # convert to gray
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    
    # detect face
    ayam_s = ayam_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=2)
    string = 'jumlah ayam : ' + str(len(ayam_s))

    # draw rectangle on the face
    for (x, y, w, h) in ayam_s:
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
    frame = cv2.putText(frame, string, (10, 450), cv2.FONT_HERSHEY_SIMPLEX, 
                        0.8, (255, 255, 0), 2)
    
    cv2.imshow('img', frame)
    return len(ayam_s)

def main():
    total_ayam = detection()
    time = [7, 0]
    jam = time[0]
    menit = time[1]
    set_kendali = "<"+str(jam)+","+str(menit)+","+str(total_ayam)+">"
    print(set_kendali)
    # msg = data_io.read()
    # sg = float(msg)
    # volume = -5.8824*float(msg) + 129.41
    # if volume < 0.0:
    #     volume = 0.0
    # mssg = set_kendali + " "+ str(sg)+ " " + str(volume)
    # print(mssg)
    # data_io.write(set_kendali)
    
if __name__ == '__main__':
    while True:
        main()
        if cv2.waitKey(1) & 0xFF==ord('q'):
            data_io.close()
            break

# release the VideoCapture
cv2.destroyAllWindows()