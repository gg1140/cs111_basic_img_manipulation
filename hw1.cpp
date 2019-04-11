// color img > b&w img
// box filter that avg all image pixels (blurring)

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat convert2grey(Mat color_img) {
    Mat bw_img(color_img.rows, color_img.cols, CV_8UC1);

    for (int i = 0; i < color_img.rows; i++) {
        for (int j = 0; j < color_img.cols; j++) {
            Vec3b pixel = color_img.at<Vec3b>(i, j);
            uchar b = pixel.val[0];
            uchar g = pixel.val[1];
            uchar r = pixel.val[2];

            bw_img.at<uchar>(i, j) = (0.1140 * b)
                                    + (0.5870 * g)
                                    + (0.2990 * r);
        }
    }
    return bw_img;
}

/* val[1] green <- val[0] blue
 * val[2] red <- val[1] green
 * val[0] blue <- val[2] red
 */
Mat swap_color_channels(Mat og_img) {
    Mat new_img(og_img.rows, og_img.cols, CV_8UC1);

    for (int i = 0; i < og_img.rows; i++) {
        for (int j = 0; j < og_img.cols; j++) {
            Vec3b pixel = og_img.at<Vec3b>(i, j);
            Vec3b new_pixel = {pixel[2], pixel[0], pixel[1]};
            new_img.at<Vec3b>(i, j) = new_pixel;
        }
    }
    return new_img;
}

/*
 * This function only behavior properly when:
 * 1. an black & white image was given
 * 2. the size of image is at least 2x2
 * 3. the kernal/filter dimension is 3x3
 */
void BoxFilterGray3(Mat og_bw_img) {
    auto edge = [c=og_bw_img.cols-1, r=og_bw_img.rows-1](int x, int y) {
        return (x == 0 || x == c || y == 0 || y == r);
    };
    Mat new_img(og_bw_img.rows, og_bw_img.cols, CV_8UC1);
    int kernal_dim = 3;
    //int* kernal = malloc(sizeof(int) * kernal_dim * kernal_dim);
/*
    for (int i = 1; i < (og_bw_img.rows - 1); i++) {
        for (int j = 1; j < (og_bw_img.cols - 1); j++) {
            uchar pixel = og_bw_img.at<uchar>(i, j);
            printf("%d\n", pixel);
            kernal[1][1] = pixel;
            kernal[0][0] = og_bw_img.at<uchar>(i - 1, j - 1);

        }
    }
*/
    for (int i = 1; i < (og_bw_img.cols - 1); i++) {
        //top and bottom edges
    }

    for (int i = 1; i < (og_bw_img.rows - 1); i++) {
        //left and right edges
    }

    return;
}

int reflect(Mat img, int x, int y) {
    auto below_bound = [](int x) {return x < 0;};
    auto over_bound = [](int x, int upper) {return x > upper;};
    auto reflect_below = [](int x) {return (x * -1) - 1;};
    auto reflect_over = [](int x, int upper) {return (upper * 2 - 1) - x;};
    int new_x = x;
    int new_y = y;
    if (below_bound(x)) {
        new_x = reflect_below(x);
    } else if (over_bound(x, img.rows - 1)) {
        new_x = reflect_over(x, img.rows);
    }

    if (below_bound(y)) {
        new_y = reflect_below(y);
    } else if (over_bound(y, img.cols - 1)) {
        new_y = reflect_over(y, img.cols);
    }
    //printf("%d,%d\n", new_x, new_y);
    return img.at<int>(new_x, new_y);
}

void fill_kernal3(Mat kernal, Mat img, int mid_x, int mid_y) {
    auto out_bound = [c=img.cols-1, r=img.rows-1](int x, int y) {
        return (x < 0 || x > r || y < 0 || y > c);
    };
    int offset_x = mid_x - 1;
    int offset_y = mid_y - 1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int lin_ind = i*3 + j;
            int temp_x = offset_x + i;
            int temp_y = offset_y + j;
            //printf("x:%d y:%d ind:%d\n", offset_x + i, offset_y + j, lin_ind);
            if (out_bound(temp_x, temp_y)) {
                kernal.at<int>(i, j) = reflect(img, temp_x, temp_y);
                //kernal[lin_ind] = img.at<uchar>(temp_x, temp_y);
                //printf("%d,%d -> %d\n", temp_x, temp_y, reflect(img, temp_x, temp_y));
            } else {
                kernal.at<int>(i, j) = (int)img.at<int>(temp_x, temp_y);
            }
        }
    }
}

/*
void mirror_padding(int* kern, int rows, int cols) {
    auto corner = [c=og_bw_img.cols-1, r=og_bw_img.rows-1](int x, int y) {
        return (x == 0 && (y == 0 || y == r)) ||
            (x == r && (y == 0 || y == r));
    };
    int cross_ind[4][2] = {{0, -1}, {-1, 0}, {1, 0}, {0, 1}}; //veritcal horizontal neighbour
    int dia_ind[4][2] = {{-1, -1}, {1, -1}, {-1, 1}, {1, 1}}; //diagonal neighbour
    int* new_kern = malloc(sizeof(int) * rows * cols);


    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << kern[i*cols + j];
        }
        cout << endl;
    }
}
*/
int main(int argc, char** argv) {
    if (argc < 2) {
        printf("specify image path\n");
        return -1;
    }

    Mat og_img;
    og_img = imread(argv[1], IMREAD_COLOR);//CV_LOAD_IMAGE_COLOR);
    //printf("number of channels = %i", og_img.channels());
    if (!og_img.data) {
        printf("No image data \n");
        return -1;
    }
    int testarr[] = {-1, -1, -1, -1, 3, 4, -1, 5, 6};//3x4
    Mat1i testmat = (Mat1i(3, 3) << 3, 1, 2, 3, 4, 5, 6, 7, 8, 9);
    Mat1i testkern(3, 3, CV_8UC1);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d|", testmat.at<int>(i, j));
        }
        cout << endl;
    }
    //reflect(testmat, 0, 3);
    fill_kernal3(testkern, testmat, 2, 2);
    //mirror_padding(testarr, 3, 4);
    /*if (argc = 3) {
        imwrite(argv[2], new_img);
    } else {
        imwrite("new.jpg", new_img);
    }*/

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d|", testkern.at<int>(i, j));
        }
        cout << endl;
    }
    return 0;
}
