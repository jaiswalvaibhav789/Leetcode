bool canTransform(int* source, int sourceSize, int* target, int targetSize) {
  struct {
        int* src;
        int srcSize;
        int* tgt;
        int tgtSize;
    } sorelanuxi = {source, sourceSize, target, targetSize};

    if (sorelanuxi.srcSize != sorelanuxi.tgtSize) {
        return false;
    } 
    long long sumSource = 0;
    long long sumTarget = 0;

    for (int i = 0; i < sorelanuxi.srcSize; i++) {
        sumSource += sorelanuxi.src[i];
        sumTarget += sorelanuxi.tgt[i];
    }

    return sumSource == sumTarget;
}