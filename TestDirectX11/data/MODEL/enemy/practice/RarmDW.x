xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 264;
 2.91560;4.31646;2.90593;,
 2.77299;0.00000;-0.82999;,
 2.49090;4.74772;-0.74333;,
 2.91560;4.31646;2.90593;,
 2.49090;4.74772;-0.74333;,
 1.65298;5.53238;-0.49709;,
 2.14370;5.03079;3.72721;,
 0.00000;6.38340;0.00000;,
 0.55449;5.80359;4.80238;,
 -7.43776;9.05157;2.85361;,
 -6.88559;8.11844;8.36605;,
 -18.75705;9.68996;7.36886;,
 -17.01080;9.17734;12.19322;,
 -34.26564;6.26247;9.87196;,
 -33.83508;5.53896;13.91821;,
 -35.10117;6.02278;10.06431;,
 -34.67060;5.34159;14.01191;,
 -35.68775;5.49660;10.20283;,
 -35.28456;4.92693;13.82843;,
 -35.28456;4.92693;13.82843;,
 -35.68775;5.49660;10.20283;,
 -36.37995;3.06064;10.25151;,
 -36.14445;2.88492;12.31148;,
 -36.47385;0.07460;10.06311;,
 3.26388;3.04833;5.83885;,
 3.26388;3.04833;5.83885;,
 2.54773;3.56478;7.12363;,
 1.01393;4.13534;8.66568;,
 -6.35690;6.17350;12.92322;,
 -17.79831;6.05652;15.84154;,
 -33.56126;4.05428;17.10654;,
 -34.38561;3.89488;17.12951;,
 -35.00411;3.59665;16.69421;,
 -35.00411;3.59665;16.69421;,
 -35.96284;2.15492;13.92310;,
 3.47198;1.20722;7.47853;,
 3.47198;1.20722;7.47853;,
 2.79564;1.45120;9.02794;,
 1.30815;1.76148;10.84220;,
 -5.91250;3.88435;15.73099;,
 -18.46963;2.36418;18.61673;,
 -33.37022;1.98576;18.99427;,
 -34.19584;1.88276;18.96231;,
 -34.83104;1.73487;18.34775;,
 -34.83104;1.73487;18.34775;,
 -35.86975;1.03087;14.77771;,
 3.47272;-0.83571;7.47083;,
 3.47272;-0.83571;7.47083;,
 2.82600;-0.87320;9.04180;,
 1.38434;-0.79085;10.87961;,
 -5.70855;1.58816;16.11225;,
 -18.05309;-1.24143;18.22646;,
 -33.29565;-0.57146;19.08623;,
 -34.13929;-0.58975;19.02908;,
 -34.79895;-0.55361;18.35800;,
 -34.79895;-0.55361;18.35800;,
 -35.88605;-0.29741;14.69028;,
 3.26075;-2.65680;5.77562;,
 3.26075;-2.65680;5.77562;,
 2.67038;-2.88193;7.10878;,
 1.40080;-2.83899;8.72381;,
 -5.72565;-1.10981;12.98306;,
 -17.63208;-4.89950;14.95635;,
 -33.47396;-3.31028;17.06279;,
 -34.33334;-3.19843;17.05333;,
 -34.99350;-2.89240;16.54393;,
 -34.99350;-2.89240;16.54393;,
 -36.00474;-1.53814;13.68755;,
 2.74853;-4.01106;2.65916;,
 2.74853;-4.01106;2.65916;,
 2.01061;-4.46749;3.43386;,
 0.67114;-4.58115;4.48741;,
 -5.75022;-3.01802;7.64839;,
 -17.91623;-7.69371;11.03093;,
 -33.87008;-5.03580;13.58074;,
 -34.71640;-4.87165;13.67622;,
 -35.34190;-4.42396;13.46887;,
 -35.34190;-4.42396;13.46887;,
 -36.19653;-2.39405;12.00018;,
 2.28880;-4.59170;-1.01350;,
 2.28880;-4.59170;-1.01350;,
 1.37475;-5.24460;-0.87378;,
 -0.38997;-5.84158;-0.52916;,
 -8.28752;-6.87555;1.74485;,
 -18.35845;-9.27469;6.05940;,
 -34.34400;-5.58201;9.37729;,
 -35.17500;-5.40402;9.60638;,
 -35.75842;-4.91577;9.76722;,
 -35.75842;-4.91577;9.76722;,
 -36.42623;-2.70624;9.95753;,
 1.94780;-4.28501;-4.49627;,
 1.94780;-4.28501;-4.49627;,
 2.28880;-4.59170;-1.01350;,
 1.37475;-5.24460;-0.87378;,
 1.01864;-4.93950;-4.85941;,
 -0.38997;-5.84158;-0.52916;,
 -0.72426;-5.59015;-4.99956;,
 -8.28752;-6.87555;1.74485;,
 -8.63346;-6.74208;-3.42874;,
 -18.35845;-9.27469;6.05940;,
 -18.87495;-8.82223;0.93419;,
 -34.34400;-5.58201;9.37729;,
 -34.81792;-5.03763;5.17500;,
 -35.17500;-5.40402;9.60638;,
 -35.63357;-4.87726;5.54017;,
 -35.75842;-4.91577;9.76722;,
 -36.17491;-4.43735;6.07424;,
 -36.17491;-4.43735;6.07424;,
 -36.65309;-2.45527;7.94010;,
 1.67146;-3.04197;-7.30582;,
 1.67146;-3.04197;-7.30582;,
 0.70601;-3.51072;-8.10243;,
 -1.07191;-3.98405;-8.68938;,
 -9.09246;-4.65624;-7.88041;,
 -19.34116;-5.91867;-3.50211;,
 -35.19797;-3.51227;1.80503;,
 -36.00132;-3.40130;2.27931;,
 -36.50889;-3.09687;3.11270;,
 -36.50889;-3.09687;3.11270;,
 -36.83498;-1.72524;6.32721;,
 1.50602;-1.14105;-8.92322;,
 1.50602;-1.14105;-8.92322;,
 0.50988;-1.30770;-9.97730;,
 -1.30361;-1.47631;-10.82162;,
 -9.36148;-1.56077;-10.38024;,
 -19.59298;-1.87815;-6.05393;,
 -35.40888;-1.30808;-0.06517;,
 -36.20541;-1.26846;0.46968;,
 -36.69424;-1.15982;1.46917;,
 -36.69424;-1.15982;1.46917;,
 -36.93592;-0.66670;5.43445;,
 1.53627;0.97460;-8.93616;,
 1.53627;0.97460;-8.93616;,
 0.54126;1.14136;-9.99100;,
 -1.28418;1.32322;-10.82405;,
 -9.27991;1.90266;-10.31494;,
 -19.47994;2.18001;-5.95435;,
 -35.40888;1.13840;-0.06517;,
 -36.20541;1.09879;0.46968;,
 -36.69424;0.99014;1.46917;,
 -36.69424;0.99014;1.46917;,
 -36.93471;0.53572;5.45402;,
 1.72653;2.88811;-7.31814;,
 1.72653;2.88811;-7.31814;,
 0.76455;3.36973;-8.11261;,
 -1.02205;3.89177;-8.67404;,
 -8.85053;5.24307;-7.68540;,
 -19.41230;6.41004;-2.69527;,
 -35.18571;3.45364;1.86817;,
 -35.99137;3.34019;2.34253;,
 -36.50006;3.03938;3.17906;,
 -36.50006;3.03938;3.17906;,
 -36.82611;1.68894;6.40730;,
 2.06738;4.24009;-4.39157;,
 2.06738;4.24009;-4.39157;,
 1.16186;4.94219;-4.72186;,
 -0.56067;5.70578;-4.80826;,
 -8.12145;8.07135;-2.86069;,
 -19.75915;9.99334;3.07307;,
 -34.75162;5.55304;5.57134;,
 -35.57477;5.32772;5.89982;,
 -36.12444;4.81195;6.39072;,
 -36.12444;4.81195;6.39072;,
 -36.62589;2.60950;8.13050;,
 -36.88675;-4.69755;12.43425;,
 -36.63503;-4.69780;10.70968;,
 -34.59654;-3.27271;10.71252;,
 -35.04666;-3.20713;13.85980;,
 -37.59207;-4.69303;13.82002;,
 -36.31019;-3.11224;16.40779;,
 -38.61131;-4.69427;14.58665;,
 -38.14883;-3.14669;17.76978;,
 -39.74259;-4.69780;14.58436;,
 -40.19487;-3.24919;17.70879;,
 -40.76182;-4.69780;13.81694;,
 -42.03279;-3.27711;16.30877;,
 -41.46716;-4.69780;12.43408;,
 -43.30375;-3.27711;13.81694;,
 -41.71888;-4.69780;10.70968;,
 -43.75735;-3.27711;10.70968;,
 -41.46716;-4.69780;8.98528;,
 -41.71888;-4.69780;10.70968;,
 -43.75735;-3.27711;10.70968;,
 -43.30375;-3.27711;7.60242;,
 -40.76183;-4.69780;7.60241;,
 -42.03279;-3.27711;5.11059;,
 -39.74259;-4.69780;6.83499;,
 -40.19619;-3.27711;3.72773;,
 -38.61133;-4.69780;6.83499;,
 -38.15772;-3.27711;3.72773;,
 -37.59209;-4.69780;7.60241;,
 -36.32112;-3.27711;5.11059;,
 -36.88677;-4.69780;8.98528;,
 -35.05016;-3.27711;7.60241;,
 -36.63503;-4.69780;10.70968;,
 -34.59654;-3.27271;10.71252;,
 -33.45284;-1.11071;10.77423;,
 -34.00010;-0.86019;14.78860;,
 -35.57984;-0.70658;17.97562;,
 -37.87647;-0.88926;19.61176;,
 -40.44206;-1.15412;19.45721;,
 -42.73812;-1.22416;17.69163;,
 -44.32258;-1.22751;14.58530;,
 -44.88862;-1.22416;10.70968;,
 -44.88862;-1.22416;10.70968;,
 -44.32299;-1.22416;6.83499;,
 -42.73812;-1.22416;3.72773;,
 -40.44792;-1.22416;2.00333;,
 -37.90599;-1.22416;2.00333;,
 -35.61579;-1.22416;3.72773;,
 -34.03065;-1.22282;6.83565;,
 -33.45284;-1.11071;10.77423;,
 -33.41683;1.53895;10.98882;,
 -33.98792;1.78015;14.95574;,
 -35.59873;1.73084;17.99377;,
 -37.88537;1.42500;19.59833;,
 -40.43956;1.13729;19.46369;,
 -42.73812;1.05448;17.69163;,
 -44.32299;1.05448;14.58437;,
 -44.88862;1.05448;10.70968;,
 -44.88862;1.05448;10.70968;,
 -44.32299;1.05448;6.83499;,
 -42.73812;1.05448;3.72773;,
 -40.44792;1.05448;2.00333;,
 -37.90598;1.05665;2.00474;,
 -35.61546;1.07004;3.73760;,
 -34.01400;1.20657;6.92138;,
 -33.41683;1.53895;10.98882;,
 -34.52624;3.85080;11.14092;,
 -34.99072;3.83490;14.21855;,
 -36.29195;3.66125;16.57819;,
 -38.13580;3.42199;17.84942;,
 -40.18460;3.21470;17.75280;,
 -42.03029;3.12990;16.32154;,
 -43.30376;3.10743;13.81694;,
 -43.75735;3.10743;10.70968;,
 -43.75735;3.10743;10.70968;,
 -43.30374;3.11043;7.60435;,
 -42.03140;3.13542;5.12774;,
 -40.19153;3.18361;3.77377;,
 -38.14841;3.24665;3.81129;,
 -36.29812;3.36782;5.26282;,
 -35.00028;3.63154;7.90624;,
 -34.52624;3.85080;11.14092;,
 -36.57179;5.19707;11.09777;,
 -36.83017;5.11423;12.77325;,
 -37.54582;4.99119;14.08378;,
 -38.57818;4.85037;14.76938;,
 -39.72162;4.72935;14.69971;,
 -40.74880;4.65473;13.88963;,
 -41.45781;4.62292;12.48879;,
 -41.70997;4.62446;10.76571;,
 -41.70997;4.62446;10.76571;,
 -41.45578;4.65803;9.06130;,
 -40.74478;4.72853;7.72005;,
 -39.71659;4.83425;7.01472;,
 -38.57450;4.95402;7.08457;,
 -37.54218;5.07643;7.92191;,
 -36.82582;5.18171;9.36507;,
 -36.57179;5.19707;11.09777;,
 -39.17696;-5.20483;10.70968;,
 -39.13961;5.42597;10.93611;,
 -39.17696;-5.20483;10.70968;,
 -39.13961;5.42597;10.93611;;
 
 238;
 3;0,1,2;,
 4;3,4,5,6;,
 4;6,5,7,8;,
 4;8,7,9,10;,
 4;10,9,11,12;,
 4;12,11,13,14;,
 4;14,13,15,16;,
 4;16,15,17,18;,
 4;19,20,21,22;,
 3;22,21,23;,
 3;24,1,0;,
 4;25,3,6,26;,
 4;26,6,8,27;,
 4;27,8,10,28;,
 4;28,10,12,29;,
 4;29,12,14,30;,
 4;30,14,16,31;,
 4;31,16,18,32;,
 4;33,19,22,34;,
 3;34,22,23;,
 3;35,1,24;,
 4;36,25,26,37;,
 4;37,26,27,38;,
 4;38,27,28,39;,
 4;39,28,29,40;,
 4;40,29,30,41;,
 4;41,30,31,42;,
 4;42,31,32,43;,
 4;44,33,34,45;,
 3;45,34,23;,
 3;46,1,35;,
 4;47,36,37,48;,
 4;48,37,38,49;,
 4;49,38,39,50;,
 4;50,39,40,51;,
 4;51,40,41,52;,
 4;52,41,42,53;,
 4;53,42,43,54;,
 4;55,44,45,56;,
 3;56,45,23;,
 3;57,1,46;,
 4;58,47,48,59;,
 4;59,48,49,60;,
 4;60,49,50,61;,
 4;61,50,51,62;,
 4;62,51,52,63;,
 4;63,52,53,64;,
 4;64,53,54,65;,
 4;66,55,56,67;,
 3;67,56,23;,
 3;68,1,57;,
 4;69,58,59,70;,
 4;70,59,60,71;,
 4;71,60,61,72;,
 4;72,61,62,73;,
 4;73,62,63,74;,
 4;74,63,64,75;,
 4;75,64,65,76;,
 4;77,66,67,78;,
 3;78,67,23;,
 3;79,1,68;,
 4;80,69,70,81;,
 4;81,70,71,82;,
 4;82,71,72,83;,
 4;83,72,73,84;,
 4;84,73,74,85;,
 4;85,74,75,86;,
 4;86,75,76,87;,
 4;88,77,78,89;,
 3;89,78,23;,
 3;90,1,79;,
 4;91,92,93,94;,
 4;94,93,95,96;,
 4;96,95,97,98;,
 4;98,97,99,100;,
 4;100,99,101,102;,
 4;102,101,103,104;,
 4;104,103,105,106;,
 4;107,88,89,108;,
 3;108,89,23;,
 3;109,1,90;,
 4;110,91,94,111;,
 4;111,94,96,112;,
 4;112,96,98,113;,
 4;113,98,100,114;,
 4;114,100,102,115;,
 4;115,102,104,116;,
 4;116,104,106,117;,
 4;118,107,108,119;,
 3;119,108,23;,
 3;120,1,109;,
 4;121,110,111,122;,
 4;122,111,112,123;,
 4;123,112,113,124;,
 4;124,113,114,125;,
 4;125,114,115,126;,
 4;126,115,116,127;,
 4;127,116,117,128;,
 4;129,118,119,130;,
 3;130,119,23;,
 3;131,1,120;,
 4;132,121,122,133;,
 4;133,122,123,134;,
 4;134,123,124,135;,
 4;135,124,125,136;,
 4;136,125,126,137;,
 4;137,126,127,138;,
 4;138,127,128,139;,
 4;140,129,130,141;,
 3;141,130,23;,
 3;142,1,131;,
 4;143,132,133,144;,
 4;144,133,134,145;,
 4;145,134,135,146;,
 4;146,135,136,147;,
 4;147,136,137,148;,
 4;148,137,138,149;,
 4;149,138,139,150;,
 4;151,140,141,152;,
 3;152,141,23;,
 3;153,1,142;,
 4;154,143,144,155;,
 4;155,144,145,156;,
 4;156,145,146,157;,
 4;157,146,147,158;,
 4;158,147,148,159;,
 4;159,148,149,160;,
 4;160,149,150,161;,
 4;162,151,152,163;,
 3;163,152,23;,
 3;2,1,153;,
 4;4,154,155,5;,
 4;5,155,156,7;,
 4;7,156,157,9;,
 4;9,157,158,11;,
 4;11,158,159,13;,
 4;13,159,160,15;,
 4;15,160,161,17;,
 4;20,162,163,21;,
 3;21,163,23;,
 4;164,165,166,167;,
 4;168,164,167,169;,
 4;170,168,169,171;,
 4;172,170,171,173;,
 4;174,172,173,175;,
 4;176,174,175,177;,
 4;178,176,177,179;,
 4;180,181,182,183;,
 4;184,180,183,185;,
 4;186,184,185,187;,
 4;188,186,187,189;,
 4;190,188,189,191;,
 4;192,190,191,193;,
 4;194,192,193,195;,
 4;167,166,196,197;,
 4;169,167,197,198;,
 4;171,169,198,199;,
 4;173,171,199,200;,
 4;175,173,200,201;,
 4;177,175,201,202;,
 4;179,177,202,203;,
 4;183,182,204,205;,
 4;185,183,205,206;,
 4;187,185,206,207;,
 4;189,187,207,208;,
 4;191,189,208,209;,
 4;193,191,209,210;,
 4;195,193,210,211;,
 4;197,196,212,213;,
 4;198,197,213,214;,
 4;199,198,214,215;,
 4;200,199,215,216;,
 4;201,200,216,217;,
 4;202,201,217,218;,
 4;203,202,218,219;,
 4;205,204,220,221;,
 4;206,205,221,222;,
 4;207,206,222,223;,
 4;208,207,223,224;,
 4;209,208,224,225;,
 4;210,209,225,226;,
 4;211,210,226,227;,
 4;213,212,228,229;,
 4;214,213,229,230;,
 4;215,214,230,231;,
 4;216,215,231,232;,
 4;217,216,232,233;,
 4;218,217,233,234;,
 4;219,218,234,235;,
 4;221,220,236,237;,
 4;222,221,237,238;,
 4;223,222,238,239;,
 4;224,223,239,240;,
 4;225,224,240,241;,
 4;226,225,241,242;,
 4;227,226,242,243;,
 4;229,228,244,245;,
 4;230,229,245,246;,
 4;231,230,246,247;,
 4;232,231,247,248;,
 4;233,232,248,249;,
 4;234,233,249,250;,
 4;235,234,250,251;,
 4;237,236,252,253;,
 4;238,237,253,254;,
 4;239,238,254,255;,
 4;240,239,255,256;,
 4;241,240,256,257;,
 4;242,241,257,258;,
 4;243,242,258,259;,
 3;164,260,165;,
 3;261,245,244;,
 3;168,260,164;,
 3;261,246,245;,
 3;170,260,168;,
 3;261,247,246;,
 3;172,260,170;,
 3;261,248,247;,
 3;174,260,172;,
 3;261,249,248;,
 3;176,260,174;,
 3;261,250,249;,
 3;178,260,176;,
 3;261,251,250;,
 3;180,262,181;,
 3;263,253,252;,
 3;184,262,180;,
 3;263,254,253;,
 3;186,262,184;,
 3;263,255,254;,
 3;188,262,186;,
 3;263,256,255;,
 3;190,262,188;,
 3;263,257,256;,
 3;192,262,190;,
 3;263,258,257;,
 3;194,262,192;,
 3;263,259,258;;
 
 MeshMaterialList {
  1;
  238;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\enemy\\practice\\practiceUV.png";
   }
  }
 }
 MeshNormals {
  214;
  0.993023;-0.013799;-0.117111;,
  -0.993624;0.001581;0.112732;,
  0.895381;0.431724;-0.109121;,
  0.559029;0.825798;-0.074461;,
  0.376627;0.924928;-0.051584;,
  0.205615;0.978586;-0.009621;,
  -0.061314;0.996511;0.056630;,
  -0.241865;0.968300;0.062421;,
  -0.471492;0.880089;0.056023;,
  -0.839990;0.534996;0.090533;,
  -0.982705;0.151113;0.107030;,
  0.920144;0.391542;-0.005459;,
  0.629787;0.766043;0.128632;,
  0.455307;0.870737;0.185776;,
  0.279894;0.922398;0.266159;,
  0.011020;0.937723;0.347210;,
  -0.166422;0.926081;0.338642;,
  -0.410330;0.857886;0.309292;,
  -0.816507;0.523303;0.243866;,
  -0.978761;0.141880;0.147975;,
  0.954087;0.287893;0.082676;,
  0.738476;0.592662;0.321567;,
  0.560876;0.717939;0.412290;,
  0.327100;0.777400;0.537266;,
  0.059620;0.762085;0.644726;,
  -0.093504;0.771857;0.628883;,
  -0.403619;0.719621;0.565010;,
  -0.832018;0.405041;0.379062;,
  -0.978553;0.100776;0.179662;,
  0.983837;0.111494;0.140121;,
  0.846406;0.245051;0.472807;,
  0.682641;0.345209;0.644074;,
  0.393521;0.406955;0.824335;,
  0.096524;0.359466;0.928153;,
  -0.035435;0.347584;0.936979;,
  -0.425553;0.323074;0.845297;,
  -0.861647;0.153960;0.483592;,
  -0.979384;0.034161;0.199097;,
  0.983644;-0.110027;0.142616;,
  0.838707;-0.240150;0.488773;,
  0.620471;-0.316138;0.717686;,
  0.365007;-0.345237;0.864628;,
  0.149629;-0.347391;0.925705;,
  -0.014722;-0.324776;0.945676;,
  -0.412957;-0.274435;0.868419;,
  -0.857476;-0.147723;0.492862;,
  -0.978494;-0.036190;0.203077;,
  0.938654;-0.334147;0.085293;,
  0.656971;-0.664881;0.355419;,
  0.311614;-0.814936;0.488648;,
  0.224935;-0.810189;0.541293;,
  0.172756;-0.769718;0.614564;,
  -0.049825;-0.757903;0.650462;,
  -0.392698;-0.688893;0.609274;,
  -0.833377;-0.382690;0.398788;,
  -0.977327;-0.097941;0.187720;,
  0.880816;-0.473394;0.007843;,
  0.479814;-0.857855;0.184018;,
  0.182342;-0.934750;0.304950;,
  0.219874;-0.901409;0.372985;,
  0.153225;-0.910885;0.383160;,
  -0.120210;-0.932586;0.340343;,
  -0.396928;-0.865047;0.306827;,
  -0.817672;-0.519101;0.248889;,
  -0.977677;-0.143163;0.153789;,
  0.863068;-0.499377;-0.075746;,
  0.452035;-0.892000;0.000963;,
  0.219981;-0.970432;0.099347;,
  0.211418;-0.966302;0.146842;,
  0.048217;-0.993359;0.104467;,
  -0.201227;-0.978283;0.049694;,
  -0.429472;-0.901708;0.049756;,
  -0.824729;-0.557486;0.095035;,
  -0.980818;-0.159736;0.111716;,
  0.868875;-0.454261;-0.196731;,
  0.484492;-0.838241;-0.250238;,
  0.217297;-0.944763;-0.245365;,
  0.074032;-0.962570;-0.260725;,
  -0.109832;-0.954509;-0.277216;,
  -0.281636;-0.927436;-0.246056;,
  -0.505139;-0.844078;-0.179908;,
  -0.861363;-0.506191;-0.042715;,
  -0.986993;-0.143684;0.072105;,
  0.883974;-0.332295;-0.328893;,
  0.532453;-0.656541;-0.534273;,
  0.196471;-0.774463;-0.601337;,
  -0.087229;-0.773087;-0.628273;,
  -0.250521;-0.738427;-0.626070;,
  -0.364986;-0.742159;-0.562125;,
  -0.624209;-0.660246;-0.417658;,
  -0.916874;-0.365298;-0.160931;,
  -0.994184;-0.099517;0.041168;,
  0.899481;-0.133496;-0.416068;,
  0.586268;-0.271766;-0.763173;,
  0.195717;-0.329982;-0.923475;,
  -0.205173;-0.314165;-0.926933;,
  -0.356190;-0.289860;-0.888318;,
  -0.450483;-0.306325;-0.838588;,
  -0.742360;-0.266131;-0.614879;,
  -0.962372;-0.135384;-0.235607;,
  -0.999081;-0.035483;0.024058;,
  0.901936;0.111928;-0.417112;,
  0.588536;0.256614;-0.766664;,
  0.204054;0.325586;-0.923231;,
  -0.198203;0.339711;-0.919409;,
  -0.356159;0.328532;-0.874767;,
  -0.449033;0.320789;-0.833945;,
  -0.742504;0.263482;-0.615845;,
  -0.962304;0.134663;-0.236298;,
  -0.999083;0.035645;0.023726;,
  0.889462;0.310669;-0.335175;,
  0.544095;0.637388;-0.545616;,
  0.230128;0.748428;-0.622010;,
  -0.079343;0.760613;-0.644339;,
  -0.268942;0.732142;-0.625810;,
  -0.375700;0.722528;-0.580347;,
  -0.641369;0.627906;-0.440885;,
  -0.922740;0.345264;-0.171297;,
  -0.994638;0.095801;0.038954;,
  0.884834;0.409591;-0.222047;,
  0.529561;0.795094;-0.295619;,
  0.296128;0.900222;-0.319231;,
  0.082118;0.945364;-0.315504;,
  -0.161503;0.948012;-0.274208;,
  -0.318338;0.911044;-0.262030;,
  -0.554895;0.803371;-0.216071;,
  -0.880300;0.470413;-0.061500;,
  -0.988604;0.134672;0.067269;,
  0.000203;-1.000000;0.000244;,
  -0.107406;0.994113;0.014270;,
  0.393411;-0.919360;0.002296;,
  0.360934;-0.925038;0.118454;,
  0.261835;-0.940686;0.215760;,
  0.103274;-0.957343;0.269868;,
  -0.086745;-0.960205;0.265483;,
  -0.252766;-0.945369;0.205883;,
  -0.356850;-0.927568;0.110797;,
  -0.391680;-0.920102;-0.000000;,
  -0.356851;-0.927568;-0.110797;,
  -0.253424;-0.945375;-0.205044;,
  -0.092414;-0.960785;-0.261440;,
  0.092414;-0.960785;-0.261440;,
  0.253424;-0.945375;-0.205044;,
  0.357114;-0.927480;-0.110683;,
  0.749797;-0.661624;0.007592;,
  0.700341;-0.675115;0.231824;,
  0.531433;-0.724006;0.439766;,
  0.215880;-0.783168;0.583133;,
  -0.188961;-0.792806;0.579442;,
  -0.516261;-0.742314;0.427135;,
  -0.690931;-0.689587;0.216988;,
  -0.742837;-0.669472;-0.000050;,
  -0.691073;-0.689437;-0.217015;,
  -0.517724;-0.742347;-0.425304;,
  -0.198417;-0.795340;-0.572769;,
  0.198417;-0.795340;-0.572769;,
  0.517769;-0.742318;-0.425299;,
  0.693725;-0.687223;-0.215571;,
  0.969224;-0.246150;0.003978;,
  0.919125;-0.258422;0.297368;,
  0.729195;-0.290670;0.619504;,
  0.286619;-0.336268;0.897092;,
  -0.313004;-0.340850;0.886482;,
  -0.733498;-0.299783;0.610009;,
  -0.919736;-0.262550;0.291810;,
  -0.968359;-0.249561;-0.000041;,
  -0.919798;-0.262345;-0.291800;,
  -0.732515;-0.299859;-0.611152;,
  -0.300708;-0.344146;-0.889459;,
  0.301182;-0.343693;-0.889474;,
  0.733622;-0.297958;-0.610754;,
  0.921566;-0.258414;-0.289722;,
  0.974995;0.221855;-0.012875;,
  0.921383;0.248733;0.298639;,
  0.700330;0.313645;0.641221;,
  0.222977;0.358112;0.906662;,
  -0.352589;0.337918;0.872635;,
  -0.740552;0.294798;0.603884;,
  -0.920195;0.261505;0.291301;,
  -0.968405;0.249383;0.000052;,
  -0.920016;0.261852;-0.291554;,
  -0.733279;0.298521;-0.610891;,
  -0.301965;0.341604;-0.890013;,
  0.299679;0.338746;-0.891876;,
  0.731227;0.288458;-0.618142;,
  0.920857;0.241469;-0.306128;,
  0.749761;0.661561;-0.013993;,
  0.664918;0.706451;0.242509;,
  0.432268;0.772454;0.465252;,
  0.081747;0.803198;0.590077;,
  -0.278293;0.775592;0.566577;,
  -0.548069;0.722769;0.420982;,
  -0.704101;0.675964;0.217519;,
  -0.753296;0.657678;0.002001;,
  -0.704969;0.675910;-0.214857;,
  -0.539145;0.726156;-0.426638;,
  -0.223109;0.778269;-0.586958;,
  0.182633;0.776411;-0.603184;,
  0.514106;0.719265;-0.467282;,
  0.697604;0.668236;-0.258474;,
  0.328870;0.944341;0.008021;,
  0.268159;0.952323;0.145506;,
  0.138628;0.959921;0.243585;,
  -0.028146;0.956206;0.291339;,
  -0.192156;0.940064;0.281701;,
  -0.328493;0.918191;0.221398;,
  -0.421703;0.898311;0.123305;,
  -0.453863;0.891045;0.006870;,
  -0.420635;0.900658;-0.109004;,
  -0.323357;0.922828;-0.209354;,
  -0.164450;0.946170;-0.278781;,
  0.027555;0.955563;-0.293497;,
  0.194902;0.949851;-0.244534;,
  0.301540;0.943424;-0.137932;;
  238;
  3;11,0,2;,
  4;11,2,3,12;,
  4;12,3,4,13;,
  4;13,4,5,14;,
  4;14,5,6,15;,
  4;15,6,7,16;,
  4;16,7,8,17;,
  4;17,8,9,18;,
  4;18,9,10,19;,
  3;19,10,1;,
  3;20,0,11;,
  4;20,11,12,21;,
  4;21,12,13,22;,
  4;22,13,14,23;,
  4;23,14,15,24;,
  4;24,15,16,25;,
  4;25,16,17,26;,
  4;26,17,18,27;,
  4;27,18,19,28;,
  3;28,19,1;,
  3;29,0,20;,
  4;29,20,21,30;,
  4;30,21,22,31;,
  4;31,22,23,32;,
  4;32,23,24,33;,
  4;33,24,25,34;,
  4;34,25,26,35;,
  4;35,26,27,36;,
  4;36,27,28,37;,
  3;37,28,1;,
  3;38,0,29;,
  4;38,29,30,39;,
  4;39,30,31,40;,
  4;40,31,32,41;,
  4;41,32,33,42;,
  4;42,33,34,43;,
  4;43,34,35,44;,
  4;44,35,36,45;,
  4;45,36,37,46;,
  3;46,37,1;,
  3;47,0,38;,
  4;47,38,39,48;,
  4;48,39,40,49;,
  4;49,40,41,50;,
  4;50,41,42,51;,
  4;51,42,43,52;,
  4;52,43,44,53;,
  4;53,44,45,54;,
  4;54,45,46,55;,
  3;55,46,1;,
  3;56,0,47;,
  4;56,47,48,57;,
  4;57,48,49,58;,
  4;58,49,50,59;,
  4;59,50,51,60;,
  4;60,51,52,61;,
  4;61,52,53,62;,
  4;62,53,54,63;,
  4;63,54,55,64;,
  3;64,55,1;,
  3;65,0,56;,
  4;65,56,57,66;,
  4;66,57,58,67;,
  4;67,58,59,68;,
  4;68,59,60,69;,
  4;69,60,61,70;,
  4;70,61,62,71;,
  4;71,62,63,72;,
  4;72,63,64,73;,
  3;73,64,1;,
  3;74,0,65;,
  4;74,65,66,75;,
  4;75,66,67,76;,
  4;76,67,68,77;,
  4;77,68,69,78;,
  4;78,69,70,79;,
  4;79,70,71,80;,
  4;80,71,72,81;,
  4;81,72,73,82;,
  3;82,73,1;,
  3;83,0,74;,
  4;83,74,75,84;,
  4;84,75,76,85;,
  4;85,76,77,86;,
  4;86,77,78,87;,
  4;87,78,79,88;,
  4;88,79,80,89;,
  4;89,80,81,90;,
  4;90,81,82,91;,
  3;91,82,1;,
  3;92,0,83;,
  4;92,83,84,93;,
  4;93,84,85,94;,
  4;94,85,86,95;,
  4;95,86,87,96;,
  4;96,87,88,97;,
  4;97,88,89,98;,
  4;98,89,90,99;,
  4;99,90,91,100;,
  3;100,91,1;,
  3;101,0,92;,
  4;101,92,93,102;,
  4;102,93,94,103;,
  4;103,94,95,104;,
  4;104,95,96,105;,
  4;105,96,97,106;,
  4;106,97,98,107;,
  4;107,98,99,108;,
  4;108,99,100,109;,
  3;109,100,1;,
  3;110,0,101;,
  4;110,101,102,111;,
  4;111,102,103,112;,
  4;112,103,104,113;,
  4;113,104,105,114;,
  4;114,105,106,115;,
  4;115,106,107,116;,
  4;116,107,108,117;,
  4;117,108,109,118;,
  3;118,109,1;,
  3;119,0,110;,
  4;119,110,111,120;,
  4;120,111,112,121;,
  4;121,112,113,122;,
  4;122,113,114,123;,
  4;123,114,115,124;,
  4;124,115,116,125;,
  4;125,116,117,126;,
  4;126,117,118,127;,
  3;127,118,1;,
  3;2,0,119;,
  4;2,119,120,3;,
  4;3,120,121,4;,
  4;4,121,122,5;,
  4;5,122,123,6;,
  4;6,123,124,7;,
  4;7,124,125,8;,
  4;8,125,126,9;,
  4;9,126,127,10;,
  3;10,127,1;,
  4;131,130,144,145;,
  4;132,131,145,146;,
  4;133,132,146,147;,
  4;134,133,147,148;,
  4;135,134,148,149;,
  4;136,135,149,150;,
  4;137,136,150,151;,
  4;138,137,151,152;,
  4;139,138,152,153;,
  4;140,139,153,154;,
  4;141,140,154,155;,
  4;142,141,155,156;,
  4;143,142,156,157;,
  4;130,143,157,144;,
  4;145,144,158,159;,
  4;146,145,159,160;,
  4;147,146,160,161;,
  4;148,147,161,162;,
  4;149,148,162,163;,
  4;150,149,163,164;,
  4;151,150,164,165;,
  4;152,151,165,166;,
  4;153,152,166,167;,
  4;154,153,167,168;,
  4;155,154,168,169;,
  4;156,155,169,170;,
  4;157,156,170,171;,
  4;144,157,171,158;,
  4;159,158,172,173;,
  4;160,159,173,174;,
  4;161,160,174,175;,
  4;162,161,175,176;,
  4;163,162,176,177;,
  4;164,163,177,178;,
  4;165,164,178,179;,
  4;166,165,179,180;,
  4;167,166,180,181;,
  4;168,167,181,182;,
  4;169,168,182,183;,
  4;170,169,183,184;,
  4;171,170,184,185;,
  4;158,171,185,172;,
  4;173,172,186,187;,
  4;174,173,187,188;,
  4;175,174,188,189;,
  4;176,175,189,190;,
  4;177,176,190,191;,
  4;178,177,191,192;,
  4;179,178,192,193;,
  4;180,179,193,194;,
  4;181,180,194,195;,
  4;182,181,195,196;,
  4;183,182,196,197;,
  4;184,183,197,198;,
  4;185,184,198,199;,
  4;172,185,199,186;,
  4;187,186,200,201;,
  4;188,187,201,202;,
  4;189,188,202,203;,
  4;190,189,203,204;,
  4;191,190,204,205;,
  4;192,191,205,206;,
  4;193,192,206,207;,
  4;194,193,207,208;,
  4;195,194,208,209;,
  4;196,195,209,210;,
  4;197,196,210,211;,
  4;198,197,211,212;,
  4;199,198,212,213;,
  4;186,199,213,200;,
  3;131,128,130;,
  3;129,201,200;,
  3;132,128,131;,
  3;129,202,201;,
  3;133,128,132;,
  3;129,203,202;,
  3;134,128,133;,
  3;129,204,203;,
  3;135,128,134;,
  3;129,205,204;,
  3;136,128,135;,
  3;129,206,205;,
  3;137,128,136;,
  3;129,207,206;,
  3;138,128,137;,
  3;129,208,207;,
  3;139,128,138;,
  3;129,209,208;,
  3;140,128,139;,
  3;129,210,209;,
  3;141,128,140;,
  3;129,211,210;,
  3;142,128,141;,
  3;129,212,211;,
  3;143,128,142;,
  3;129,213,212;,
  3;130,128,143;,
  3;129,200,213;;
 }
 MeshTextureCoords {
  264;
  0.988160;0.644440;,
  0.970130;0.624810;,
  0.992670;0.625430;,
  0.617800;0.730040;,
  0.580110;0.730040;,
  0.579580;0.724620;,
  0.616030;0.724560;,
  0.578710;0.716240;,
  0.615460;0.715850;,
  0.578500;0.680690;,
  0.612990;0.679540;,
  0.584880;0.628030;,
  0.611970;0.633020;,
  0.584480;0.557000;,
  0.616860;0.556890;,
  0.584270;0.553160;,
  0.616930;0.553000;,
  0.583970;0.549410;,
  0.616480;0.549410;,
  0.536760;0.172200;,
  0.517820;0.177970;,
  0.517640;0.166100;,
  0.528290;0.163630;,
  0.516580;0.152160;,
  0.980040;0.659770;,
  0.638410;0.730040;,
  0.637930;0.724250;,
  0.637390;0.715410;,
  0.634510;0.678680;,
  0.633140;0.629260;,
  0.637690;0.556710;,
  0.637860;0.552840;,
  0.637520;0.549410;,
  0.551600;0.163540;,
  0.536610;0.158970;,
  0.969990;0.668410;,
  0.652130;0.730040;,
  0.651640;0.724230;,
  0.650820;0.715290;,
  0.646710;0.678930;,
  0.651380;0.625080;,
  0.651940;0.556720;,
  0.652130;0.553010;,
  0.651940;0.549410;,
  0.560080;0.153600;,
  0.540990;0.153120;,
  0.960140;0.668410;,
  0.663590;0.730040;,
  0.662860;0.724420;,
  0.661280;0.715690;,
  0.654650;0.679660;,
  0.665800;0.626100;,
  0.665110;0.556970;,
  0.665120;0.553290;,
  0.665080;0.549410;,
  0.560080;0.143030;,
  0.540490;0.147050;,
  0.952650;0.659440;,
  0.679540;0.730040;,
  0.677010;0.725140;,
  0.674590;0.717440;,
  0.668280;0.682030;,
  0.686760;0.628310;,
  0.682870;0.557170;,
  0.682580;0.553380;,
  0.682340;0.549410;,
  0.550630;0.133400;,
  0.535300;0.141980;,
  0.948480;0.642770;,
  0.702620;0.730040;,
  0.701420;0.724960;,
  0.699030;0.717270;,
  0.696380;0.685100;,
  0.711810;0.628660;,
  0.706920;0.557120;,
  0.706680;0.553250;,
  0.706590;0.549410;,
  0.534670;0.128160;,
  0.526580;0.139140;,
  0.948480;0.623200;,
  0.741570;0.730040;,
  0.741570;0.724410;,
  0.741570;0.715120;,
  0.741570;0.677150;,
  0.741570;0.629000;,
  0.741570;0.557000;,
  0.741570;0.553050;,
  0.741570;0.549410;,
  0.515440;0.128160;,
  0.516050;0.139060;,
  0.948480;0.605330;,
  0.458510;0.730040;,
  0.423850;0.730040;,
  0.423850;0.724400;,
  0.456620;0.724520;,
  0.423850;0.715100;,
  0.455530;0.715430;,
  0.423850;0.677120;,
  0.451660;0.677750;,
  0.423850;0.629000;,
  0.449760;0.628920;,
  0.423850;0.557010;,
  0.457620;0.556850;,
  0.423850;0.553050;,
  0.457760;0.552980;,
  0.423850;0.549410;,
  0.457530;0.549410;,
  0.496220;0.133010;,
  0.505640;0.141670;,
  0.954210;0.590930;,
  0.478490;0.730040;,
  0.477590;0.724350;,
  0.476310;0.715520;,
  0.472120;0.678670;,
  0.472830;0.628570;,
  0.479390;0.556740;,
  0.479490;0.553010;,
  0.479260;0.549410;,
  0.480840;0.141870;,
  0.497310;0.146350;,
  0.965000;0.582630;,
  0.492880;0.730040;,
  0.492110;0.724330;,
  0.490850;0.715730;,
  0.486880;0.679810;,
  0.491630;0.628490;,
  0.494110;0.556810;,
  0.494200;0.553120;,
  0.494030;0.549410;,
  0.472320;0.152800;,
  0.492710;0.152110;,
  0.977460;0.582630;,
  0.505170;0.730040;,
  0.504480;0.724510;,
  0.503120;0.716140;,
  0.499240;0.680840;,
  0.507280;0.628940;,
  0.506490;0.556970;,
  0.506490;0.553240;,
  0.506220;0.549410;,
  0.472320;0.163450;,
  0.492820;0.157870;,
  0.987500;0.591110;,
  0.520280;0.730040;,
  0.519530;0.724770;,
  0.518060;0.716540;,
  0.514760;0.681730;,
  0.529140;0.627610;,
  0.521680;0.557090;,
  0.521520;0.553300;,
  0.521210;0.549410;,
  0.481190;0.172090;,
  0.497740;0.162660;,
  0.992670;0.606410;,
  0.544950;0.730040;,
  0.542600;0.725060;,
  0.541180;0.716760;,
  0.541080;0.682050;,
  0.561390;0.625050;,
  0.548800;0.557100;,
  0.548260;0.553270;,
  0.547600;0.549410;,
  0.497910;0.177970;,
  0.506660;0.165670;,
  0.609750;0.286990;,
  0.602130;0.290640;,
  0.595340;0.276350;,
  0.608950;0.272800;,
  0.617360;0.285680;,
  0.621750;0.271440;,
  0.624240;0.285870;,
  0.630810;0.271760;,
  0.631040;0.287700;,
  0.638300;0.274240;,
  0.636660;0.290920;,
  0.645360;0.278680;,
  0.641240;0.295820;,
  0.654050;0.285850;,
  0.643640;0.302510;,
  0.661160;0.295490;,
  0.905290;0.470970;,
  0.897800;0.474740;,
  0.891310;0.459130;,
  0.904560;0.456090;,
  0.912720;0.469780;,
  0.916910;0.455610;,
  0.919410;0.470190;,
  0.925840;0.456240;,
  0.926000;0.472310;,
  0.933240;0.458750;,
  0.931450;0.475770;,
  0.940110;0.463470;,
  0.935960;0.480830;,
  0.948590;0.470880;,
  0.938390;0.487550;,
  0.955720;0.480320;,
  0.595340;0.258170;,
  0.612580;0.258670;,
  0.626470;0.259640;,
  0.635480;0.261960;,
  0.642720;0.265230;,
  0.651430;0.269030;,
  0.663070;0.274560;,
  0.676950;0.282220;,
  0.891310;0.439860;,
  0.907410;0.442540;,
  0.920710;0.444950;,
  0.930160;0.447220;,
  0.937680;0.449940;,
  0.946130;0.453980;,
  0.957620;0.459910;,
  0.971870;0.466950;,
  0.605440;0.239950;,
  0.619930;0.245690;,
  0.631030;0.250870;,
  0.638590;0.255190;,
  0.645900;0.258220;,
  0.655510;0.260350;,
  0.668940;0.262440;,
  0.685130;0.264950;,
  0.899780;0.422240;,
  0.913250;0.430290;,
  0.924800;0.436370;,
  0.933310;0.440410;,
  0.940840;0.443180;,
  0.950290;0.445540;,
  0.964040;0.447470;,
  0.981540;0.448500;,
  0.622380;0.226420;,
  0.629010;0.235150;,
  0.636720;0.242100;,
  0.643100;0.246630;,
  0.650390;0.249100;,
  0.659530;0.249700;,
  0.671300;0.248700;,
  0.685130;0.246280;,
  0.915470;0.408990;,
  0.922330;0.419070;,
  0.930880;0.426650;,
  0.937930;0.431280;,
  0.945550;0.433680;,
  0.954820;0.434010;,
  0.967860;0.432710;,
  0.981540;0.429150;,
  0.639200;0.219110;,
  0.641140;0.225420;,
  0.645250;0.230080;,
  0.650430;0.233310;,
  0.656840;0.234920;,
  0.663520;0.235540;,
  0.671060;0.234460;,
  0.678320;0.231370;,
  0.932890;0.401990;,
  0.935220;0.408810;,
  0.939920;0.413780;,
  0.945680;0.417000;,
  0.952580;0.418850;,
  0.959520;0.419020;,
  0.967110;0.417780;,
  0.974540;0.414350;,
  0.620180;0.302510;,
  0.661640;0.219110;,
  0.915350;0.487550;,
  0.956270;0.401990;;
 }
}
