import cv2

# load dataset
ayam_cascade = cv2.CascadeClassifier('warna-warni2-cascade.xml')

# To capture frame
image = cv2.imread("1.jpg")

gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

def main():
    # detect face
    ayam_s = ayam_cascade.detectMultiScale(gray, scaleFactor=1.8, minNeighbors=1)
    string = 'jumlah ayam : ' + str(len(ayam_s))

    # draw rectangle on the face
    for (x, y, w, h) in ayam_s:
        cv2.rectangle(image, (x, y), (x+w, y+h), (0, 255, 0), 2)
    frame = cv2.putText(image, string, (10, 450), cv2.FONT_HERSHEY_SIMPLEX, 
                                    0.8, (10, 255, 0), 2)
    cv2.imshow('img', frame)

if __name__ == '__main__':
    while True:
        main()
        if cv2.waitKey(1) & 0xFF==ord('q'):
            break

# release the VideoCapture
cv2.destroyAllWindows()