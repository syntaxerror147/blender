/* SPDX-FileCopyrightText: 2023 Blender Authors
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

#include "node_geometry_util.hh"

 namespace blender::nodes::node_geo_dmatrix_cc {
 
static void node_declare(NodeDeclarationBuilder &b)
{
  b.add_input<decl::Int>("Rows")
      .default_value(1)
      .min(1)
      .description("Number of rows");
  b.add_input<decl::Int>("Columns")
      .default_value(1)
      .min(1)
      .description("Number of columns");
  auto &input = b.add_input<decl::Float>("Value")
                    .default_value(0.0f)
                    .description("Input value")
                    .supports_field();
  b.add_output<decl::Float>("Output")
      .description("Output value")
      .dependent_field({input.index()});
}
 
static void node_geo_exec(GeoNodeExecParams params)
{
  /* Extract inputs to avoid unused variable warnings */
  const int rows = params.extract_input<int>("Rows");
  const int columns = params.extract_input<int>("Columns");
  (void)rows;
  (void)columns;
  
  /* Forward the input value (can be a single value or a field) */
  SocketValueVariant value = params.extract_input<SocketValueVariant>("Value");
  params.set_output("Output", std::move(value));
}
 
 static void node_register()
 {
   static blender::bke::bNodeType ntype;
 
   geo_node_type_base(&ntype, "GeometryNodeDMatrix", GEO_NODE_DMATRIX);
   ntype.ui_name = "DMatrix";
   ntype.ui_description = "DMatrix node";
   ntype.enum_name_legacy = "DMATRIX";
   ntype.nclass = NODE_CLASS_GEOMETRY;
   ntype.geometry_node_execute = node_geo_exec;
   ntype.declare = node_declare;
   blender::bke::node_register_type(ntype);
 }
 NOD_REGISTER_NODE(node_register)
 
 }  // namespace blender::nodes::node_geo_dmatrix_cc 