#include <stdio.h>
#include <stdlib.h>

int main( void )
{
    int a;

    a = fmin( 10, 10 );
    printf( "The value is: %d\n", a );
    return EXIT_SUCCESS;
}
/*
int main()
{
    struct rgb_img *im;
    struct rgb_img *cur_im;
    struct rgb_img *grad;
    double *best;
    int *path;

    read_in_img(&im, "6x5.bin");
    
    for(int i = 0; i < 5; i++){
        printf("i = %d\n", i);
        calc_energy(im,  &grad);
        dynamic_seam(grad, &best);
        recover_path(best, grad->height, grad->width, &path);
        remove_seam(im, &cur_im, path);

        char filename[200];
        sprintf(filename, "img%d.bin", i);
        write_img(cur_im, filename);


        destroy_image(im);
        destroy_image(grad);
        free(best);
        free(path);
        im = cur_im;
    }
    destroy_image(im);
}


int main() // Do I need to worry about freeing
{
    struct rgb_img* im1;
    struct rgb_img* im2;
    struct rgb_img* grad;
    double* best_arr;
    int* path;
    read_in_img(&im1, "6x5.bin");
    calc_energy(im1, &grad);
    print_grad(grad);
    dynamic_seam(grad, &best_arr);
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            printf("%f\t", best_arr[i * 6 + j]);
        }
        printf("\n");
    }
    recover_path(best_arr, 5, 6, &path);
    for (int i = 0; i < 5; i++)
    {
        printf("%d\t", path[i]);
    }

}
*/