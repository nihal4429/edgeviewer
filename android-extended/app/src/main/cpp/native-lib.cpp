#include <jni.h>
#include <vector>
#include <cstring>

#ifdef USE_OPENCV
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#endif

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_example_edgeviewer_native_NativeProcessor_processFrame(
        JNIEnv *env, jobject, jbyteArray nv21_, jint width, jint height) {

    const int w = width;
    const int h = height;
    const int ySize = w * h;

    jbyte *nv21 = env->GetByteArrayElements(nv21_, nullptr);

    std::vector<unsigned char> out(ySize, 0);

#ifdef USE_OPENCV
    cv::Mat yuv(h + h/2, w, CV_8UC1, (unsigned char*)nv21);
    cv::Mat bgr, gray, edges;
    cv::cvtColor(yuv, bgr, cv::COLOR_YUV2BGR_NV21);
    cv::cvtColor(bgr, gray, cv::COLOR_BGR2GRAY);
    cv::Canny(gray, edges, 50, 150, 3, false);
    std::memcpy(out.data(), edges.data, ySize);
#else
    std::memcpy(out.data(), (unsigned char*)nv21, ySize);
#endif

    env->ReleaseByteArrayElements(nv21_, nv21, 0);

    jbyteArray result = env->NewByteArray(ySize);
    env->SetByteArrayRegion(result, 0, ySize, (jbyte*)out.data());
    return result;
}
