#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QtDebug>
#include <QDesktopWidget>


int areSame(double A[][3], double B[][3])
{
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            if (A[i][j] != B[i][j])
                return 0;
    return 1;
}

bool isGray(unsigned char **image, int *width, int *height, int *channels){

    size_t image_size = (*width) * (*height) * (*channels);

    for(unsigned char *p = (*image); p != (*image) + image_size; p += (*channels)){
        if(!(*p == *(p+1) && *p == *(p+2) && *(p+1) == *(p+2))){
            return false;
        }
    }

    return true;
}

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    if(*it == '-'){
        it++;
        while (it != s.end() && std::isdigit(*it)) ++it;
        return !s.empty() && it == s.end();
    }
    else{
        while (it != s.end() && (std::isdigit(*it) || *it == '.')) ++it;
        return !s.empty() && it == s.end();
    }

}

void imgToGrey(unsigned char **image, int *width, int *height, int *channels){



    size_t image_size = (*width) * (*height) * (*channels);

    int gray_channels;

    if((*channels) == 4){
        gray_channels = 2;
    }
    else{
        gray_channels = 1;
    }

    size_t gray_image_size = (*width) * (*height) * gray_channels;

    unsigned char *gray_image = (unsigned char*)malloc(gray_image_size);

    uint8_t color;

    for(unsigned char *p = (*image), *pg = gray_image; p != (*image) + image_size; p += (*channels), pg += gray_channels){
        color = (uint8_t) ((*p * 0.299) +  (*(p + 1) * 0.587) +  (*(p + 2) * 0.114));
        *pg = color;
        if((*channels) == 4){
            *(pg + 1) = *(p + 3);
        }
    }


    if(*channels != 1){
        *channels = gray_channels;



        *image = gray_image;
    }


}


void flipHorizontally(unsigned char **image, int *width, int *height, int *channels){

    size_t image_size = (*width) * (*height) * (*channels);

    unsigned char *flipped = (unsigned char*)malloc(image_size);



    for(unsigned char *p = (*image) + (*width-1) * (*channels), *pf = flipped; pf != flipped + (*width) * (*channels); p -= (*channels), pf += (*channels)){


        for(unsigned char *x = p, *xf = pf; x != p + (*height) * (*width) * (*channels); x += (*width) * (*channels), xf += (*width) * (*channels)){
            if((*channels) == 1){
                *xf = (uint8_t) *x;
            }
            if((*channels) == 2){
                *xf = (uint8_t) *x;
                *(xf + 1) = (uint8_t) *(x + 1);
            }
            if((*channels) == 3){
                *xf = (uint8_t) *x;
                *(xf + 1) = (uint8_t) *(x + 1);
                *(xf + 2) = (uint8_t) *(x + 2);
            }
            if((*channels) == 4){
                *xf = (uint8_t) *x;
                *(xf + 1) = (uint8_t) *(x + 1);
                *(xf + 2) = (uint8_t) *(x + 2);
                *(xf + 3) = (uint8_t) *(x + 3);
            }

        }
    }
    *image = flipped;


}

void flipVertically(unsigned char **image, int *width, int *height, int *channels){



    size_t image_size = (*width) * (*height) * (*channels);

    unsigned char *flipped = (unsigned char*)malloc(image_size);



    for(unsigned char *p = (*image) + (*height-1) * (*width) * (*channels), *pf = flipped; pf != flipped + image_size; p -= (*channels) * (*width), pf += (*channels) * (*width)){
        //memcpy(pf, p, 8 * (*channels) * (*width));


        for(unsigned char *x = p, *xf = pf; x != p +  (*width) * (*channels); x += (*channels), xf += (*channels)){
            if((*channels) == 1){
                *xf = (uint8_t) *x;
            }
            if((*channels) == 2){
                *xf = (uint8_t) *x;
                *(xf + 1) = (uint8_t) *(x + 1);
            }
            if((*channels) == 3){
                *xf = (uint8_t) *x;
                *(xf + 1) = (uint8_t) *(x + 1);
                *(xf + 2) = (uint8_t) *(x + 2);
            }
            if((*channels) == 4){
                *xf = (uint8_t) *x;
                *(xf + 1) = (uint8_t) *(x + 1);
                *(xf + 2) = (uint8_t) *(x + 2);
                *(xf + 3) = (uint8_t) *(x + 3);
            }

        }
    }



    *image = flipped;




}


void quantization(unsigned char **image, int *width, int *height, int *channels, int n){


    imgToGrey(image, width, height, channels);



    int biggest = 0, lowest = 255, tam_int;
    float x, y;

    size_t image_size = (*width) * (*height) * (*channels);

    unsigned char *newImage = (unsigned char*)malloc(image_size);

    for(unsigned char *p = (*image); p != (*image) + image_size; p += (*channels)){
        if(*p > biggest){
            biggest = *p;
        }
        if(*p < lowest){
            lowest = *p;
        }
    }

    //printf("lowest: %d, biggest: %d", lowest, biggest);

    tam_int = biggest - lowest + 1;

    if(n < tam_int){
        int tb = floor(tam_int / n);

        //printf("tamanho: %d", tb);

        //int flagTeste = 1;

        for(unsigned char *p = (*image), *pg = newImage; p != (*image) + image_size; p += (*channels), pg += (*channels)){

            x = (lowest - 0.5);
            y = (lowest - 0.5 + tb);

            int flag = 1;

            //int contador = 0;
            while(flag){
                if(*p >= x && *p < y){
                    int color = (int)(round((x + y)/2));

                    if(color > 255){
                        *pg = 255;
                    }
                    else if(color < 0){
                        *pg = 0;
                    }
                    else{
                        *pg = color;
                    }
                    flag = 0;
                }
                else{
                    x = y;
                    y = y + tb;
                    //contador++;
                }
            }
            /*printf("antes: %d, depois: %d, contador: %d, tb: %d", *p, *pg, contador, tb);
            if(flagTeste) {
                printf("antes: %d, depois: %d, contador: %d, tb: %d", *p, *pg, contador, tb);
                flagTeste = 0;
            }
            */
        }



        *image = newImage;


    }


}

void brightness(unsigned char **image, int *width, int *height, int *channels, int n){



    size_t image_size = (*width) * (*height) * (*channels);

    unsigned char *newImage = (unsigned char*)malloc(image_size);

    for(unsigned char *p = (*image), *pg = newImage; p != (*image) + image_size; p += 1, pg += 1){
        int result = *p + n;
        if(result >= 255){
            *pg = 255;
        }
        else if(result <= 0){
            *pg = 0;
        }
        else{
            *pg = result;
        }
    }

    *image = newImage;
}

void contrast(unsigned char **image, int *width, int *height, int *channels, double n){



    size_t image_size = (*width) * (*height) * (*channels);

    unsigned char *newImage = (unsigned char*)malloc(image_size);

    for(unsigned char *p = (*image), *pg = newImage; p != (*image) + image_size; p += 1, pg += 1){
        int result = *p * n;
        if(result >= 255){
            *pg = 255;
        }
        else if(result <= 0){
            *pg = 0;
        }
        else{
            *pg = result;
        }
    }

    *image = newImage;
}

void negative(unsigned char **image, int *width, int *height, int *channels){



    size_t image_size = (*width) * (*height) * (*channels);

    unsigned char *newImage = (unsigned char*)malloc(image_size);

    for(unsigned char *p = (*image), *pg = newImage; p != (*image) + image_size; p += 1, pg += 1){
        int result = 255 - *p;
        if(result >= 255){
            *pg = 255;
        }
        else if(result <= 0){
            *pg = 0;
        }
        else{
            *pg = result;
        }
    }

    *image = newImage;
}


void histogramFunction(unsigned char **image3, int *width2, int *height2, int *channels2){

    int width = *width2, height = *height2, channels = *channels2;


    int histogramHeight = 256;

    unsigned char *image = *image3;


    size_t image_size = width * height;

    int histogram[256];
    for(int i = 0; i< 256;i++){
        histogram[i] = 0;
    }

    if(channels != 1){
        imgToGrey(&image, &width, &height, &channels);
    }

    if(channels != 1){
        imgToGrey(&image, &width, &height, &channels);
    }






    if (channels == 1){
        for(unsigned char *p = image; p != image + image_size; p += channels){
            histogram[*p] += 1;
        }


        int max = 0;
        for(int i = 0; i < 256; i++){
            if(histogram[i] > max){
                max = histogram[i];
            }
        }





        int counter = histogramHeight;

        double normal = max / (double)histogramHeight;


        int histogramSize = 256 * histogramHeight;



        unsigned char *histogramImage = (unsigned char*)malloc(histogramSize);


        int index = 0;

        for(unsigned char *p = histogramImage; p != histogramImage + histogramSize; p += channels * 256){
            for(unsigned char *pg = p; pg != p + (channels * 256); pg += channels){


                    if(histogram[index] / (counter * normal) >= 1){
                        *pg = 0;
                    }
                    else{
                        *pg = 255;
                    }

                    index++;


            }
            counter--;
            index = 0;
        }







        stbi_write_jpg("histogram.jpg", 256, histogramHeight, 1, histogramImage, 100);


    }


}

void equalizationGrey(unsigned char **image, int *width, int *height, int *channels){

    size_t img_size = (*width) * (*height) * (*channels);
    unsigned char *modified_img = (unsigned char *)malloc(img_size);

    int histogram[256] = {0};

    for(unsigned char *p = *image; p != *image + img_size; p += *channels){
        histogram[*p] += 1;
    }


    int hist_cum[256] = {0};
    float a = 255.0 / ((*width) * (*height));

    hist_cum[0] = histogram[0];

    for(int i = 1; i < 256; i++){
        hist_cum[i] = hist_cum[i-1] + histogram[i];
        //printf("%d\n", hist_cum[i]);
    }

    for(int i = 0; i < 256; i++){
        hist_cum[i] = hist_cum[i] * a;
        printf("%d\n", hist_cum[i]);
    }

    for(unsigned char *p = *image, *pg = modified_img; p != *image + img_size; p += *channels, pg += *channels){
        *pg = hist_cum[*p];
        *(pg+1) = hist_cum[*(p)];
        *(pg+2) = hist_cum[*(p)];
    }

    *image = modified_img;

}

void equalizationRGB(unsigned char **image, int *width, int *height, int *channels){

    size_t img_size = (*width) * (*height) * (*channels);
    unsigned char *modified_img = (unsigned char *)malloc(img_size);

    int histogram[256] = {0};

    for(unsigned char *p = *image; p != *image + img_size; p += *channels){
        histogram[*p] += 1;
    }


    int hist_cum[256] = {0};
    float alpha = 255.0 / ((*width) * (*height));

    hist_cum[0] = histogram[0];

    for(int i = 1; i < 256; i++){
        hist_cum[i] = hist_cum[i-1] + histogram[i];
        //printf("%d\n", hist_cum[i]);
    }

    for(int i = 0; i < 256; i++){
        hist_cum[i] = hist_cum[i] * alpha;
        //printf("%d\n", hist_cum[i]);
    }

    for(unsigned char *p = *image, *pg = modified_img; p != *image + img_size; p += *channels, pg += *channels){
        *pg = hist_cum[*p];
        *(pg+1) = hist_cum[*(p+1)];
        *(pg+2) = hist_cum[*(p+2)];
    }

    *image = modified_img;

}


void matching(unsigned char **imageSrc, int *width, int *height, int *channels, unsigned char **imageTarget, int *widthTarget, int *heightTarget, int *channelsTarget){
    size_t img_size = (*width) * (*height) * (*channels);
    size_t img_sizeTar = (*widthTarget) * (*heightTarget) * (*channelsTarget);



    int histogramSrc[256] = {0};
    int histogramSrcCum[256] = {0};
    int histogramTarget[256] = {0};
    int histogramTargetCum[256] = {0};

    int HM[256] = {0};


    for(unsigned char *p = *imageSrc; p != *imageSrc + img_size; p += *channels){
        histogramSrc[*p] += 1;
    }

    float alpha = 255.0 / ((*width) * (*height));

    histogramSrcCum[0] = histogramSrc[0];

    for(int i = 1; i < 256; i++){
        histogramSrcCum[i] = histogramSrcCum[i-1] + histogramSrc[i];
        //printf("%d\n", hist_cum[i]);
    }

    for(int i = 0; i < 256; i++){
        histogramSrcCum[i] = histogramSrcCum[i] * alpha;
        //printf("%d\n", hist_cum[i]);
    }

    for(unsigned char *p = *imageTarget; p != *imageTarget + img_sizeTar; p += *channels){
        histogramTarget[*p] += 1;
    }

    alpha = 255.0 / ((*widthTarget) * (*heightTarget));

    histogramTargetCum[0] = histogramTarget[0];

    for(int i = 1; i < 256; i++){
        histogramTargetCum[i] = histogramTargetCum[i-1] + histogramTarget[i];
        //printf("%d\n", hist_cum[i]);
    }

    for(int i = 0; i < 256; i++){
        histogramTargetCum[i] = histogramTargetCum[i] * alpha;
        //printf("%d\n", hist_cum[i]);
    }

    for(int i = 0; i < 256; i++){
       int value = histogramSrcCum[i];
       int distance = 256;
       int position;

       for(int j = 0;j < 256; j++){
           if(std::abs(value - histogramTargetCum[j]) < distance){
               distance = std::abs(value - histogramTargetCum[j]);
               position = j;
           }
       }

       HM[i] = position;
    }

    for(int i = 0; i < 256; i++){
        printf("%d\n", HM[i]);
    }

    for(unsigned char *p = *imageSrc; p != *imageSrc + img_size; p += *channels){
        *p = HM[*p];
        *(p+1) = HM[*(p+1)];
        *(p+2) = HM[*(p+2)];
    }



}


void convolution(unsigned char **image, int *width, int *height, int *channels, double value1, double value2, double value3, double value4, double value5, double value6, double value7, double value8, double value9){





    unsigned char *modified_img = (unsigned char *)malloc((*width) * (*height) * (*channels));

    double filterA[3][3] = {{-1, 0, 1}, {-1, 0, 1}, {-1, 0, 1}};
    double filterB[3][3] = {{-1, -1, -1}, {0, 0, 0}, {1, 1, 1}};
    double filterC[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    double filterD[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    double filter[3][3];
    filter[0][0] = value1;
    filter[0][1] = value2;
    filter[0][2] = value3;
    filter[1][0] = value4;
    filter[1][1] = value5;
    filter[1][2] = value6;
    filter[2][0] = value7;
    filter[2][1] = value8;
    filter[2][2] = value9;

    int flag = 0;

    if(areSame(filter, filterA)){
        flag = 1;
    }
    if(areSame(filter, filterB)){
        flag = 1;
    }
    if(areSame(filter, filterC)){
        flag = 1;
    }
    if(areSame(filter, filterD)){
        flag = 1;
    }


    for(int y = 0; y < (*height); y+=1){
        for(int x = 0; x < (*width) * (*channels); x+=3){
            double new_pixel =
            (double)(*(*image + x + y * (*width) * (*channels)))*filter[1][1] +
            (double)(*(*image + x + (y+1) * (*width) * (*channels)))*filter[2][1] +
            (double)(*(*image + x + (y-1) * (*width) * (*channels)))*filter[0][1] +
            (double)(*(*image + x+3 + y * (*width) * (*channels)))*filter[1][2] +
            (double)(*(*image + x-3 + y * (*width) * (*channels)))*filter[1][0] +
            (double)(*(*image + x+3 + (y+1) * (*width) * (*channels)))*filter[2][2] +
            (double)(*(*image + x+3 + (y-1) * (*width) * (*channels)))*filter[0][2] +
            (double)(*(*image + x-3 + (y+1) * (*width) * (*channels)))*filter[2][0] +
            (double)(*(*image + x-3 + (y-1) * (*width) * (*channels)))*filter[0][0];

            if(flag){
                new_pixel += 127;
            }

            if(new_pixel > 255){
                *(modified_img + x + y * (*width) * (*channels)) = 255;
                *(modified_img + x+1 + y * (*width) * (*channels)) = 255;
                *(modified_img + x+2 + y * (*width) * (*channels)) = 255;
            }
            else if(new_pixel < 0){
                *(modified_img + x + y * (*width) * (*channels)) = 0;
                *(modified_img + x+1 + y * (*width) * (*channels)) = 0;
                *(modified_img + x+2 + y * (*width) * (*channels)) = 0;
            }
            else{
                *(modified_img + x + y * (*width) * (*channels)) = (uint8_t)new_pixel;
                *(modified_img + x+1 + y * (*width) * (*channels)) = (uint8_t)new_pixel;
                *(modified_img + x+2 + y * (*width) * (*channels)) = (uint8_t)new_pixel;
            }
        }
    }



    *image = modified_img;
}



void turn(unsigned char **image, int *width, int *height, int *channels){



    size_t image_size = (*width) * (*height) * (*channels);

    unsigned char *newImage = (unsigned char *)malloc(image_size);

    for(int y = 0; y < (*height); y++){
        for(int x = 0; x < (*width) * (*channels); x += 3){
            *(newImage + ((*height) * x) + (y * 3)) = *(*image + x + ((*width) * (3 * y)));
            *(newImage + ((*height) * x) + (y * 3) + 1) = *(*image + x + ((*width) * (3 * y)) + 1);
            *(newImage + ((*height) * x) + (y * 3) + 2) = *(*image + x + ((*width) * (3 * y)) + 2);
        }
    }

    *image = newImage;

    int aux = *width;
    *width = *height;
    *height = aux;



    flipHorizontally(image, width, height, channels);



}


void zoomOut(unsigned char **image, int *width, int *height, int *channels, int sx, int sy){

    size_t image_size = (*width) * (*height) * (*channels);

    size_t newImage_size = std::ceil(*width / sx) * std::ceil(*height / sy) * (*channels);

    unsigned char *newImage = (unsigned char *)malloc(image_size);


    int cumR = 0;
    int cumG = 0;
    int cumB = 0;

    int numPixels = 0;

    int counterX = 0;
    int counterY = 0;
    for(unsigned char *pg = newImage; pg < newImage + newImage_size; pg += *channels){

        counterX++;
        if(counterX >= (*width / sx)){
            counterX = 0;
            counterY++;
            if(counterY >= (*height) / sy){
                break;
            }
        }

        numPixels = 0;
        cumR = 0;
        cumG = 0;
        cumB = 0;

        unsigned char *initialP = *image + (counterY * sy * (*width) * (*channels));





        for(unsigned char *p = initialP; p < *image + image_size && p < initialP + ((*width) * (*channels) * sy); p += (*width) * (*channels)){
            unsigned char *initialPZ = p + (counterX * sx * (*channels));
            for(unsigned char *pz = initialPZ; pz < p + (*width) * (*channels) && pz < initialPZ + (sx * (*channels)); pz += (*channels)){
                cumR += *pz;
                cumG += *(pz+1);
                cumB += *(pz+2);
                numPixels++;
            }
        }
        *pg = cumR / numPixels;
        *(pg+1) = cumG / numPixels;
        *(pg+2) = cumB / numPixels;



    }

    *width = *width/sx;
    *height = *height/sy;

    *image = newImage;

}

void zoomIn(unsigned char **image, int *width, int *height, int *channels){

    size_t image_size = (*width)*(*height)*(*channels);
        unsigned char* newImage = (unsigned char*)malloc(image_size*4);

        for(int i = 0; i < (*height); i++){
            for(int j = 0; j < (*width)*(*channels); j+=3){
                *(newImage + i*(*width)*(*channels)*2*2 + j*2) = *(*image + j + i*(*width)*(*channels));
                *(newImage + i*(*width)*(*channels)*2*2 + j*2 + 1) = *(*image + j + i*(*width)*(*channels) + 1);
                *(newImage + i*(*width)*(*channels)*2*2 + j*2 + 2) = *(*image + j + i*(*width)*(*channels) + 2);
            }
            for(int j = 3; j < (*width)*(*channels)*2; j+=6){
                if((j+3) != ((*width)*(*channels)*2)){
                    *(newImage + i*(*width)*(*channels)*2*2 + j) = (*(newImage + i*(*width)*(*channels)*2*2 + j - 3) + *(newImage + i*(*width)*(*channels)*2*2 + j + 3))/2;
                    *(newImage + i*(*width)*(*channels)*2*2 + j + 1) = (*(newImage + i*(*width)*(*channels)*2*2 + j - 2) + *(newImage + i*(*width)*(*channels)*2*2 + j + 4))/2;
                    *(newImage + i*(*width)*(*channels)*2*2 + j + 2) = (*(newImage + i*(*width)*(*channels)*2*2 + j - 1) + *(newImage + i*(*width)*(*channels)*2*2 + j + 5))/2;
                }
            }
        }
        for(int j = 0; j < (*width)*(*channels)*2; j++){
            for(int i = 1; i < (*height)*2; i+=2){
                if(i + 1 != (*height)*2){
                    *(newImage + i*(*width)*(*channels)*2 + j) = (*(newImage + (i-1)*(*width)*(*channels)*2 + j) + *(newImage + (i+1)*(*width)*(*channels)*2 + j))/2;
                }
            }
        }

        *image = newImage;
        *width = *width * 2;
        *height = *height * 2;
}







MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    int width, height, channels;

    QString filename = QFileDialog::getOpenFileName(this, "Open image", "C://");


    unsigned char *image = stbi_load(filename.toStdString().c_str(), &width, &height, &channels, 0);


    /*
    imgToGrey(&image, &width, &height, &channels);
    flipHorizontally(&image, &width, &height, &channels);
    flipVertically(&image, &width, &height, &channels);
    flipVertically(&image, &width, &height, &channels);
    flipVertically(&image, &width, &height, &channels);
    */

    stbi_write_jpg("working.jpg", width, height, channels, image, 100);

    stbi_write_jpg("initial.jpg", width, height, channels, image, 100);

    QDesktopWidget desktop;
    QRect screenGeometry = desktop.screenGeometry();
    int heightS = screenGeometry.height();
    int widthS = screenGeometry.width();

    int x;
    int y;

    QImage image1("initial.jpg");
    ui->label->setPixmap(QPixmap::fromImage(image1));

    x=(widthS / 2) -50 -width;
    y=(heightS - height) / 2.0 -50;
    ui->label->setGeometry(x,y,width,height);

    QImage image2("working.jpg");
    ui->label_2->setPixmap(QPixmap::fromImage(image2));

    x=(widthS / 2) + 50;
    y=(heightS - height) / 2.0 -50;
    ui->label_2->setGeometry(x,y,width,height);




    /*
    width = image2.width();
    height = image2.height();

    ui->label->setPixmap(QPixmap::fromImage(image2));
    ui->label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

    ui->label_2->setPixmap(QPixmap::fromImage(image2));
    ui->label_2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    */
}

void MainWindow::on_pushButton_2_clicked()
{

    int width, height, channels;




    unsigned char *image = stbi_load("working.jpg", &width, &height, &channels, 0);

    imgToGrey(&image, &width, &height, &channels);



    stbi_write_jpg("working.jpg", width, height, channels, image, 100);

    image = stbi_load("working.jpg", &width, &height, &channels, 0);



    QImage image2("working.jpg");
    ui->label_2->setPixmap(QPixmap::fromImage(image2));


}

void MainWindow::on_pushButton_3_clicked()
{
    int width, height, channels;

    unsigned char *image = stbi_load("working.jpg", &width, &height, &channels, 0);

    flipHorizontally(&image, &width, &height, &channels);

    stbi_write_jpg("working.jpg", width, height, channels, image, 100);

    QImage image2("working.jpg");
    ui->label_2->setPixmap(QPixmap::fromImage(image2));
    ui->label_2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
}

void MainWindow::on_pushButton_4_clicked()
{
    int width, height, channels;

    unsigned char *image = stbi_load("working.jpg", &width, &height, &channels, 0);

    flipVertically(&image, &width, &height, &channels);

    stbi_write_jpg("working.jpg", width, height, channels, image, 100);

    QImage image2("working.jpg");
    ui->label_2->setPixmap(QPixmap::fromImage(image2));
    ui->label_2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
}

void MainWindow::on_pushButton_5_clicked()
{
    if(is_number(ui->lineEdit->text().toStdString().c_str())){
        int quantizationN = ui->lineEdit->text().toInt();

        int width, height, channels;
        unsigned char *image = stbi_load("working.jpg", &width, &height, &channels, 0);

        quantization(&image, &width, &height, &channels, quantizationN);

        stbi_write_jpg("working.jpg", width, height, channels, image, 100);

        QImage image2("working.jpg");
        ui->label_2->setPixmap(QPixmap::fromImage(image2));
        ui->label_2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    int width, height, channels;
    QString selfilter = tr("JPEG (*.jpg *.jpeg)");

    QString filename = QFileDialog::getSaveFileName(this, "Save as:", "C:",  tr("All files (*.*);;JPEG (*.jpg *.jpeg);;TIFF (*.tif)" ), &selfilter);


    unsigned char *image = stbi_load("working.jpg", &width, &height, &channels, 0);




    stbi_write_jpg(filename.toStdString().c_str(), width, height, channels, image, 100);





}

void MainWindow::on_pushButton_7_clicked()
{

    if(is_number(ui->lineEdit_3->text().toStdString().c_str())){
        int brightnessN = ui->lineEdit_3->text().toInt();

        int width, height, channels;
        unsigned char *image = stbi_load("working.jpg", &width, &height, &channels, 0);

        brightness(&image, &width, &height, &channels, brightnessN);


        stbi_write_jpg("working.jpg", width, height, channels, image, 100);

        QImage image2("working.jpg");
        ui->label_2->setPixmap(QPixmap::fromImage(image2));
        ui->label_2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

    }


}


void MainWindow::on_pushButton_8_clicked()
{
    if(is_number(ui->lineEdit_2->text().toStdString().c_str())){
        double contrastN = ui->lineEdit_2->text().toDouble();

        int width, height, channels;
        unsigned char *image = stbi_load("working.jpg", &width, &height, &channels, 0);

        contrast(&image, &width, &height, &channels, contrastN);


        stbi_write_jpg("working.jpg", width, height, channels, image, 100);

        QImage image2("working.jpg");
        ui->label_2->setPixmap(QPixmap::fromImage(image2));
        ui->label_2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

    }
}

void MainWindow::on_pushButton_10_clicked()
{
    int width, height, channels;
    unsigned char *image = stbi_load("initial.jpg", &width, &height, &channels, 0);
    stbi_write_jpg("working.jpg", width, height, channels, image, 100);

    QDesktopWidget desktop;
    QRect screenGeometry = desktop.screenGeometry();
    int heightS = screenGeometry.height();
    int widthS = screenGeometry.width();

    int x=(widthS / 2) + 50;
    int y=(heightS - height) / 2.0 -50;
    ui->label_2->setGeometry(x,y,width,height);

    QImage image2("working.jpg");
    ui->label_2->setPixmap(QPixmap::fromImage(image2));
    ui->label_2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
}

void MainWindow::on_pushButton_9_clicked()
{
    int width, height, channels;

    unsigned char *image = stbi_load("working.jpg", &width, &height, &channels, 0);



    negative(&image, &width, &height, &channels);

    stbi_write_jpg("working.jpg", width, height, channels, image, 100);

    QImage image2("working.jpg");
    ui->label_2->setPixmap(QPixmap::fromImage(image2));
    ui->label_2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
}

void MainWindow::on_pushButton_11_clicked()
{
    int width, height, channels;
    unsigned char *image = stbi_load("working.jpg", &width, &height, &channels, 0);


    histogramFunction(&image, &width, &height, &channels);


    imgToGrey(&image, &width, &height, &channels);


    stbi_write_jpg("working.jpg", width, height, channels, image, 100);

    QImage image2("working.jpg");
    ui->label_2->setPixmap(QPixmap::fromImage(image2));
    ui->label_2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);





    QLabel *label_img = new QLabel (this);
    label_img->setWindowFlags(Qt::Window);
    QImage hist("histogram.jpg");
    label_img->setPixmap(QPixmap::fromImage(hist));
    label_img->show();







}

void MainWindow::on_pushButton_12_clicked()
{

    int width, height, channels;

    unsigned char *image = stbi_load("working.jpg", &width, &height, &channels, 0);




    if (isGray(&image, &width, &height, &channels)){

        histogramFunction(&image, &width, &height, &channels);

        QLabel *label_img = new QLabel (this);
        label_img->setWindowFlags(Qt::Window);
        QImage hist("histogram.jpg");
        label_img->setPixmap(QPixmap::fromImage(hist));
        label_img->show();

        equalizationGrey(&image, &width, &height, &channels);

        histogramFunction(&image, &width, &height, &channels);

        QLabel *label_img2 = new QLabel (this);
        label_img2->setWindowFlags(Qt::Window);
        QImage hist2("histogram.jpg");
        label_img2->setPixmap(QPixmap::fromImage(hist2));
        label_img2->show();
    }

    else{
        equalizationRGB(&image, &width, &height, &channels);
    }


    stbi_write_jpg("working.jpg", width, height, channels, image, 100);

    QImage image2("working.jpg");
    ui->label_2->setPixmap(QPixmap::fromImage(image2));
    ui->label_2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

}

void MainWindow::on_pushButton_13_clicked()
{
    int widthTarget, heightTarget, channelsTarget;
    int width, height, channels;

    QString filename = QFileDialog::getOpenFileName(this, "Open image", "C://");


    unsigned char *imageTarget = stbi_load(filename.toStdString().c_str(), &widthTarget, &heightTarget, &channelsTarget, 0);

    unsigned char *imageSrc = stbi_load("working.jpg", &width, &height, &channels, 0);

    matching(&imageSrc, &width, &height, &channels, &imageTarget, &widthTarget, &heightTarget, &channelsTarget);

    stbi_write_jpg("working.jpg", width, height, channels, imageSrc, 100);

    QImage image2("working.jpg");
    ui->label_2->setPixmap(QPixmap::fromImage(image2));
    ui->label_2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
}

void MainWindow::on_pushButton_14_clicked()
{
    if(     is_number(ui->kernel1->text().toStdString().c_str()) &&
            is_number(ui->kernel2->text().toStdString().c_str()) &&
            is_number(ui->kernel3->text().toStdString().c_str()) &&
            is_number(ui->kernel4->text().toStdString().c_str()) &&
            is_number(ui->kernel5->text().toStdString().c_str()) &&
            is_number(ui->kernel6->text().toStdString().c_str()) &&
            is_number(ui->kernel7->text().toStdString().c_str()) &&
            is_number(ui->kernel8->text().toStdString().c_str()) &&
            is_number(ui->kernel9->text().toStdString().c_str())){

        double value1 = ui->kernel1->text().toDouble();
        double value2 = ui->kernel2->text().toDouble();
        double value3 = ui->kernel3->text().toDouble();
        double value4 = ui->kernel4->text().toDouble();
        double value5 = ui->kernel5->text().toDouble();
        double value6 = ui->kernel6->text().toDouble();
        double value7 = ui->kernel7->text().toDouble();
        double value8 = ui->kernel8->text().toDouble();
        double value9 = ui->kernel9->text().toDouble();

        int width, height, channels;
        unsigned char *image = stbi_load("working.jpg", &width, &height, &channels, 0);

        convolution(&image, &width, &height, &channels, value1, value2, value3, value4, value5, value6, value7,value8,value9);


        stbi_write_jpg("working.jpg", width, height, channels, image, 100);

        QImage image2("working.jpg");
        ui->label_2->setPixmap(QPixmap::fromImage(image2));
        ui->label_2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

    }
}

void MainWindow::on_pushButton_15_clicked()
{
    int width, height, channels;

    unsigned char *image = stbi_load("working.jpg", &width, &height, &channels, 0);

    turn(&image, &width, &height, &channels);

    stbi_write_jpg("working.jpg", width, height, channels, image, 100);

    QDesktopWidget desktop;
    QRect screenGeometry = desktop.screenGeometry();
    int heightS = screenGeometry.height();
    int widthS = screenGeometry.width();

    int x=(widthS / 2) + 50;
    int y=(heightS - height) / 2.0 -50;
    ui->label_2->setGeometry(x,y,width,height);


    QImage image2("working.jpg");
    ui->label_2->setPixmap(QPixmap::fromImage(image2));
    ui->label_2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
}

void MainWindow::on_pushButton_16_clicked()
{

    if(is_number(ui->lineEdit_4->text().toStdString().c_str()) && is_number(ui->lineEdit_5->text().toStdString().c_str())){
        int sx= ui->lineEdit_4->text().toInt();
        int sy= ui->lineEdit_5->text().toInt();


        int width, height, channels;

        unsigned char *image = stbi_load("working.jpg", &width, &height, &channels, 0);



        zoomOut(&image, &width, &height, &channels, sx, sy);

        stbi_write_jpg("working.jpg", width, height, channels, image, 100);

        QDesktopWidget desktop;
        QRect screenGeometry = desktop.screenGeometry();
        int heightS = screenGeometry.height();
        int widthS = screenGeometry.width();

        int x=(widthS / 2) + 50;
        int y=(heightS - height) / 2.0 -50;
        ui->label_2->setGeometry(x,y,width,height);


        QImage image2("working.jpg");
        ui->label_2->setPixmap(QPixmap::fromImage(image2));
        ui->label_2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    }
}

void MainWindow::on_pushButton_17_clicked()
{
    int width, height, channels;

    unsigned char *image = stbi_load("working.jpg", &width, &height, &channels, 0);

    zoomIn(&image, &width, &height, &channels);

    stbi_write_jpg("working.jpg", width, height, channels, image, 100);

    QDesktopWidget desktop;
    QRect screenGeometry = desktop.screenGeometry();
    int heightS = screenGeometry.height();
    int widthS = screenGeometry.width();

    int x=(widthS / 2) + 50;
    int y=(heightS - height) / 2.0 -50;
    ui->label_2->setGeometry(x,y,width,height);


    QImage image2("working.jpg");
    ui->label_2->setPixmap(QPixmap::fromImage(image2));
    ui->label_2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
}
