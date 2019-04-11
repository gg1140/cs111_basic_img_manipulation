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

Mat swap_color_channels(Mat og_img) {
    Mat new_img(og_img.rows, og_img.cols, CV_8UC3);

    for (int i = 0; i < og_img.rows; i++) {
        for (int j = 0; j < og_img.cols; j++) {
            Vec3b pixel = og_img.at<Vec3b>(i, j);
            Vec3b new_pixel = {pixel[1], pixel[0], pixel[2]}; //Switching green with blue

            //Vec3b new_pixel = {pixel[0], pixel[2], pixel[1]}; //Switching red with green

            //Vec3b new_pixel = {pixel[2], pixel[1], pixel[0]}; //Switching blue with red
            new_img.at<Vec3b>(i, j) = new_pixel;
        }
    }
    return new_img;
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
    return img.at<int>(new_x, new_y);
}

Mat fill_kernal3(Mat img, int mid_x, int mid_y) {
    auto out_bound = [c=img.cols-1, r=img.rows-1](int x, int y) {
        return (x < 0 || x > r || y < 0 || y > c);
    };
    int offset_x = mid_x - 1;
    int offset_y = mid_y - 1;
    Mat kernal(3, 3, CV_8UC1);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int lin_ind = i*3 + j;
            int temp_x = offset_x + i;
            int temp_y = offset_y + j;
            if (out_bound(temp_x, temp_y)) {
                kernal.at<uchar>(i, j) = reflect(img, temp_x, temp_y);
                //kernal.at<uchar>(i, j) = 0; uncomment this for zero padding
            } else {
                kernal.at<uchar>(i, j) = img.at<uchar>(temp_x, temp_y);
            }
        }
    }
    return kernal;
}

/*
 * This function only behavior properly when:
 * 1. an black & white image was given
 * 2. the size of image is at least 2x2
 * 3. the kernal/filter dimension is 3x3
 */
Mat BoxFilterGray3(Mat og_bw_img) {
    /*auto edge = [c=og_bw_img.cols-1, r=og_bw_img.rows-1](int x, int y) {
        return (x == 0 || x == c || y == 0 || y == r);
    };*/
    Mat new_img(og_bw_img.rows, og_bw_img.cols, CV_8UC1);
    //Mat1i kernal(kernal_dim, kernal_dim, CV_8UC1);
    for (int i = 0; i < og_bw_img.rows; i++) {
        for (int j = 0; j < og_bw_img.cols; j++) {
            Mat kernal = fill_kernal3(og_bw_img, i, j);
            int sum = 0;
            for (int s = 0; s < 3; s++) {
                for (int t = 0; t < 3; t++) {
                    sum += kernal.at<uchar>(s, t);
                }
            }
            new_img.at<uchar>(i, j) = uchar(sum / 9.0);
        }
    }
    return new_img;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("specify image path\n");
        return -1;
    }

    Mat og_img;
    og_img = imread(argv[1], IMREAD_COLOR);//IMREAD_GRAYSCALE);

    if (!og_img.data) {
        printf("No image data \n");
        return -1;
    }

    Mat new_img = swap_color_channels(og_img);

    if (argc = 3) {
        imwrite(argv[2], new_img);
    } else {
        imwrite("new.jpg", new_img);
    }
    return 0;
}
