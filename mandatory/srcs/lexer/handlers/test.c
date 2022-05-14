// if ((int)ft_strlen(tmp) > op_len)
    // {
    //     // next_space(line, &end);
    //     next_op(line, &end);
        
    //     // printf("end: %zu\n", end);
    //     // exit(0);
    //     data->files->out = (char **)ft_doubrealloc((void **)data->files->out, len + 1);
    //     exit_free_if(!data->files->out, data, "allocation failed");
    //     data->files->out[len] = ft_substr(line, index + op_len, end);
    //     exit_free_if(!data->files->out[len], data, "allocation failed");
    //     if ((access(data->files->out[len], F_OK) != ENOENT))
    //     {
    //         if (access(data->files->out[len], R_OK) == EACCES)

    //             free_if(1, data, "permission denied");
    //             return false;
    //     }
    //     index = end;
    //     next_space(line, &index);
    //     skip_space(line, &index);
    // }
    // else
    // {
    //     /*
    //         if !filename:
    //             error.
    //             exit.
    //         else:
    //             store filename.
    //             tokonize the operator.
    //             update index.
    //     */
    //     next_space(line, &index);
    //     skip_space(line, &index);
    //     data->files->out = (char **)ft_doubrealloc((void **)data->files->out, len + 1);
    //     end = index;
    //     next_space(line, &end);
    //     exit_free_if(!data->files->out, data, "allocation failed");
    //     data->files->out[len] = ft_substr(line, index, end);
    //     if (!ft_validfname(data->files->out[len]))
    //     {
    //         free_if(1, data, "invalid filename");
    //         return false;
    //     }
    //     next_space(line, &index);
    //     skip_space(line, &index);
    //     free(tmp);
    // }