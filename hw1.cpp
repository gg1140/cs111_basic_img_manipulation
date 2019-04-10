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
 */
void BoxFilterGray3(Mat og_bw_img) {
    auto edge = [c=og_bw_img.cols-1, r=og_bw_img.rows-1](int x, int y) {
        return (x == 0 || x == c || y == 0 || y == r);
    };
    Mat new_img(og_bw_img.rows, og_bw_img.cols, CV_8UC1);

    for (int i = 0; i < og_bw_img.rows; i++) {
        for (int j = 0; j < og_bw_img.cols; j++) {
            uchar pixel = og_bw_img.at<uchar>(i, j);
            printf("%d\n", pixel);
        }
    }
    return;
}

void mirror_padding(int* kern, int rows, int cols) {
    /*auto corner = [c=og_bw_img.cols-1, r=og_bw_img.rows-1](int x, int y) {
        return (x == 0 && (y == 0 || y == r)) ||
            (x == r && (y == 0 || y == r));
    };*/
    int cross_ind[4][2] = {{0, -1}, {-1, 0}, {1, 0}, {0, 1}}; //veritcal horizontal neighbour
    int dia_ind[4][2] = {{-1, -1}, {1, -1}, {-1, 1}, {1, 1}}; //diagonal neighbour
    int* new_kern = (int*) malloc(sizeof(int) * rows * cols);
/*
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int pixel = kern[i][j];
            printf("%d\n", pixel);
            if (pixel < 0) { //if it is an empty pixel
                int new_pixel = -1;
                for (int s = 0; s < 4; s++) { //look for non-empty horizontal vertical neighbour
                    if (kern[cross_ind[s][0]][cross_ind[s][1]] > 0 && new_pixel > 0) {
                        new_pixel= kern[cross_ind[s][0]][cross_ind[s][1]];
                    }
                }
                if (new_pixel < 0) {
                    for (int t = 0; t < 4; t++) { //
                        if (kern.at<uchar>(dia_ind[t][0], dia_ind[t][1]) > 0) {
                            new_pixel= kern.at<uchar>(dia_ind[t][0], dia_ind[t][1]);
                        }
                    }
                }
            }
        }
    }
*/
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << kern[i*cols + j];
        }
        cout << endl;
    }
}

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
    int testarr[] = {-1, -1, -1, -1, -1, 3, 4, 4, -1, 5, 6, 1};//3x4
    mirror_padding(testarr, 3, 4);
    /*if (argc = 3) {
        imwrite(argv[2], new_img);
    } else {
        imwrite("new.jpg", new_img);
    }*/

    return 0;
}
