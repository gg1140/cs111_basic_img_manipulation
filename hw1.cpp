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

/*
 * kernal h[n] is a M points signal
 * for i = 0 to M - 1, sum(h[j] * x[i - j])
 * Both Mat parameters must have the same dimension
 * Both mat parameters must be single channel
 */
template <typename kT, typename sT> //kernal type, sample type
sT convol_sum(Mat& kernal, Mat& samples) {
    if (kernal.total() == samples.total()) {
        float sum = 0;
        for (int i = 0; i < kernal.rows; i++) {
            for (int j = 0; j < kernal.cols; j++) {
                float sample_pix = (float)samples.at<sT>(i, j);
                float kernal_pix = (float)kernal.at<kT>(i, j);
                sum += sample_pix * kernal_pix;
            }
        }
        return (sT)round(sum);
    } else {
        printf("Error: size of input Mats does not matches");
        exit(-1);
    }
}

/*
 * Return a Point type containing row and col position
 * obtained from reflecting a position outside of the img boundary
 * with its closest img boundary row & col position
 * Point(col, row), Point.x = col, Point.y = row
 */
Point reflect(int x, int y, int height, int width) {
    auto below_bound = [](int x) {return x < 0;};
    auto over_bound = [](int x, int upper) {return x > upper;};
    auto reflect_index = [] (int x, int edge_val) {return (2 * edge_val) - 1 - x;};

    int new_x = x;
    int new_y = y;

    if (below_bound(x)) {
        new_x = reflect_index(x, 0);
    } else if (over_bound(x, height - 1)) {
        new_x = reflect_index(x, height);
    }

    if (below_bound(y)) {
        new_y = reflect_index(y, 0);
    } else if (over_bound(y, width - 1)) {
        new_y = reflect_index(y, width);
    }

    return Point(new_y, new_x);
}

/*
 * Point(col, row), Point.x = col, Point.y = row
 */
template <typename T>
Mat gather_samples(Mat& img, Point pix_pos, Size kernal) {
    auto out_bound = [c=img.cols-1, r=img.rows-1](int x, int y) {
        return (x < 0 || x > r || y < 0 || y > c);
    };

    Mat samples(kernal, img.type());
    int x = pix_pos.y - kernal.height/2; //x,y are 1st element's position
    int y = pix_pos.x - kernal.width/2; //of the kernal centered at pix_pos

    for (int i = 0; i < samples.rows; i++) {
        for (int j = 0; j < samples.cols; j++) {
            int ofset_x = x + i;
            int ofset_y = y + j;
            if (out_bound(ofset_x, ofset_y)) {
                samples.at<T>(i, j) =
                    img.at<T>(reflect(ofset_x, ofset_y, img.rows, img.cols));
                //kernal.at<uchar>(i, j) = 0; //uncomment this for zero padding
            } else {
                samples.at<T>(i, j) = img.at<T>(ofset_x, ofset_y);
            }
        }
    }
    return samples;
}

/*
 * This function only behavior properly when:
 * 1. an black & white image was given
 * 2. the size of image is at least 2x2
 * 3. the kernal/filter dimension is 3x3
 */
Mat BoxFilterGray3(Mat og_bw_img) {
    auto edge = [c=og_bw_img.cols-1, r=og_bw_img.rows-1](int x, int y) {
        return (x == 0 || x == c || y == 0 || y == r);
    };

    float filter_val[9] = {1/9.0f, 1/9.0f, 1/9.0f,
                            1/9.0f, 1/9.0f, 1/9.0f,
                            1/9.0f, 1/9.0f, 1/9.0f};
    Mat filter = Mat_<float>(3, 3, filter_val);
    Mat new_img(og_bw_img.rows, og_bw_img.cols, CV_8UC1);

    for (int i = 0; i < new_img.rows; i++) {
        for (int j = 0; j < new_img.cols; j++) {
            Mat samples =
                gather_samples<uchar>(og_bw_img, Point(j, i), filter.size());
            new_img.at<uchar>(i, j) = convol_sum<float, uchar>(filter, samples);
        }
    }
    return new_img;
}

template <typename T>
void printMat(Mat& img) {
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.rows; j++) {
            cout << "|" << img.at<T>(i, j);
        }
        cout << endl;
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("specify image path\n");
        return -1;
    }

    Mat og_img = imread(argv[1], IMREAD_GRAYSCALE);

    if (!og_img.data) {
        printf("No image data \n");
        return -1;
    }

    Mat new_img = BoxFilterGray3(og_img);//swap_color_channels(og_img);

    if (argc = 3) {
        imwrite(argv[2], new_img);
    } else {
        imwrite("new.jpg", new_img);
    }
    return 0;
}
