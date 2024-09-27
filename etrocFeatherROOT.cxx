/**
 * @file etrocFeatherROOT.cxx
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief Convert ETROC Feather (Apache Arrow IPC Format) Data to ROOT File Format
 * @version 0.1
 * @date 2024-09-24
 *
 * @copyright Copyright (c) 2024
 *
 */

// Headers for C++
#include <iostream>
#include "Hit.h"
#include "TFile.h"
#include "TTree.h"
#include "TObject.h"

#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include <arrow/api.h>
#include <arrow/compute/cast.h>
#include <arrow/dataset/dataset.h>
#include <arrow/dataset/discovery.h>
#include <arrow/dataset/file_base.h>
#include <arrow/dataset/file_ipc.h>
#include <arrow/dataset/file_parquet.h>
#include <arrow/dataset/scanner.h>
#include <arrow/filesystem/filesystem.h>
#include <arrow/ipc/writer.h>
#include <arrow/util/iterator.h>
#include <parquet/arrow/writer.h>
#include "arrow/compute/expression.h"

namespace ds = arrow::dataset;
namespace fs = arrow::fs;
namespace cp = arrow::compute;

arrow::Result<std::shared_ptr<arrow::Table>> ScanWholeDataset(
    const std::shared_ptr<fs::FileSystem> &filesystem,
    const std::shared_ptr<ds::FileFormat> &format, const std::string &base_dir)
{
    // Create a dataset by scanning the filesystem for files
    fs::FileSelector selector;
    selector.base_dir = "base_dir";
    ARROW_ASSIGN_OR_RAISE(
        auto factory, ds::FileSystemDatasetFactory::Make(filesystem, selector, format,
                                                         ds::FileSystemFactoryOptions()));
    ARROW_ASSIGN_OR_RAISE(auto dataset, factory->Finish());
    // Print out the fragments
    ARROW_ASSIGN_OR_RAISE(auto fragments, dataset->GetFragments())
    for (const auto &fragment : fragments)
    {
        std::cout << "Found fragment: " << (*fragment)->ToString() << std::endl;
    }
    // Read the entire dataset as a Table
    ARROW_ASSIGN_OR_RAISE(auto scan_builder, dataset->NewScan());
    ARROW_ASSIGN_OR_RAISE(auto scanner, scan_builder->Finish());
    return scanner->ToTable();
}

// arrow::Result<std::string> CreateExampleFeatherDataset(
//     const std::shared_ptr<fs::FileSystem> &filesystem, const std::string &root_path)
// {
//     auto base_path = root_path + "/feather_dataset";
//     ARROW_RETURN_NOT_OK(filesystem->CreateDir(base_path));
//     // Create an Arrow Table
//     ARROW_ASSIGN_OR_RAISE(auto table, CreateTable());
//     // Write it into two Feather files
//     ARROW_ASSIGN_OR_RAISE(auto output,
//                           filesystem->OpenOutputStream(base_path + "/data1.feather"));
//     ARROW_ASSIGN_OR_RAISE(auto writer,
//                           arrow::ipc::MakeFileWriter(output.get(), table->schema()));
//     ARROW_RETURN_NOT_OK(writer->WriteTable(*table->Slice(0, 5)));
//     ARROW_RETURN_NOT_OK(writer->Close());
//     ARROW_ASSIGN_OR_RAISE(output,
//                           filesystem->OpenOutputStream(base_path + "/data2.feather"));
//     ARROW_ASSIGN_OR_RAISE(writer,
//                           arrow::ipc::MakeFileWriter(output.get(), table->schema()));
//     ARROW_RETURN_NOT_OK(writer->WriteTable(*table->Slice(5)));
//     ARROW_RETURN_NOT_OK(writer->Close());
//     return base_path;
// }

arrow::Status RunDatasetDocumentation(const std::string &format_name,
                                      const std::string &uri, const std::string &mode)
{
    std::string base_path;
    std::shared_ptr<ds::FileFormat> format;
    std::string root_path;
    ARROW_ASSIGN_OR_RAISE(auto fs, fs::FileSystemFromUri(uri, &root_path));

    // format = std::make_shared<ds::IpcFileFormat>();
    // ARROW_ASSIGN_OR_RAISE(base_path, CreateExampleFeatherDataset(fs, root_path));

    std::shared_ptr<arrow::Table> table;

    ARROW_ASSIGN_OR_RAISE(table, ScanWholeDataset(fs, format, base_path));

    std::cout << "Read " << table->num_rows() << " rows" << std::endl;
    std::cout << table->ToString() << std::endl;
    return arrow::Status::OK();
}

int main(int argc, char *argv[])
{
    const Char_t *inFileName = "/home/abhishek/analysis/etroc_analysis/ETROC2/data/feather.txt";

    std::ifstream inputFile(inFileName);

    if (!inputFile.is_open())
    {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    std::vector<std::string> fileNames;

    while (inputFile)
    {
        std::string path;
        std::getline(inputFile, path);
        std::cout << path << std::endl;
        if (path.empty())
        {
            continue;
        }
        fileNames.push_back(path);
    }
    std::cout << fileNames.size() << std::endl;

    std::string uri = fileNames.at(0);
    std::string format_name = "feather";
    std::string mode = "no_filter";
    auto status = RunDatasetDocumentation(format_name, uri, mode);

    return EXIT_SUCCESS;
}