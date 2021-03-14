#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QtDebug>
#include <QDesktopWidget>


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
        while (it != s.end() && std::isdigit(*it)) ++it;
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

void contrast(unsigned char **image, int *width, int *height, int *channels, int n){



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

        printf("%d", *channels);

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
            //printf("%d\n", hist_cum[i]);
        }

        for(unsigned char *p = *image, *pg = modified_img; p != *image + img_size; p += *channels, pg += *channels){
            *pg = (uint8_t)hist_cum[*p];
            *(pg+1) = (uint8_t)hist_cum[*p];
            *(pg+2) = (uint8_t)hist_cum[*p];
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
        *(pg+1) = hist_cum[*(p+1)];
        *(pg+2) = hist_cum[*(p+2)];
    }

    *image = modified_img;

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
        int contrastN = ui->lineEdit_2->text().toInt();

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
